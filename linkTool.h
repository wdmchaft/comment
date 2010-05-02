#ifndef LINKTOOL_H
#define LINKTOOL_H

/**  This file is part of comment
*
*  File: linkTool.h
*  Created: 2009
*  Author: Jonathan Verner <jonathan.verner@matfyz.cz>
*  License: GPL v2 or later
*
*  Copyright (C) 2010 Jonathan Verner <jonathan.verner@matfyz.cz>
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Library General Public
*  License as published by the Free Software Foundation; either
*  version 2 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Library General Public License for more details.
*
*  You should have received a copy of the GNU Library General Public License
*  along with this library; see the file COPYING.LIB.  If not, write to
*  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
*  Boston, MA 02110-1301, USA.
*/

#include "abstractTool.h"

#include <QtCore/QString>

class toolBox;
class linkAnnotation;

namespace PoDoFo {
    class PdfDestination;
}



class linkTool : public abstractTool {
    Q_OBJECT
private:

    struct destination {
        int page;
        QString name,type;
        QRectF viewPort;
        double value;
    };

    QList<destination> targets;
    QString addDestination( int page, QRectF viewPort, QString name = "" );
    QString addDestination( PoDoFo::PdfDestination &dest );
    static QPixmap *icon;
    static int nameCounter;

public:
    linkTool( pdfScene *Scene, toolBox *ToolBar, QStackedWidget *EditArea);
    virtual abstractAnnotation *processAnnotation( PoDoFo::PdfAnnotation *annotation, pdfCoords *transform );
    virtual void newActionEvent( const QPointF *ScenePos );
    virtual bool acceptEventsFor( QGraphicsItem *item );
    friend class linkAnnotation;
};

class linkAnnotation : public abstractAnnotation {
    public:
        linkAnnotation( linkTool *tool, PoDoFo::PdfAnnotation *linkAnnot = NULL, pdfCoords *transform = NULL );
        static bool isA( PoDoFo::PdfAnnotation *annotation );
        virtual void saveToPdfPage( PoDoFo::PdfDocument *document, PoDoFo::PdfPage *pg, pdfCoords *coords );
};



#endif // LINKTOOL_H
