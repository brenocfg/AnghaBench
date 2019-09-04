#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double Thickness; void* Join; scalar_t__ DashPhase; scalar_t__ NumDashes; int /*<<< orphan*/ * Dashes; int /*<<< orphan*/  MiterLimit; int /*<<< orphan*/  Cap; } ;
typedef  TYPE_1__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
typedef  int /*<<< orphan*/  uiDrawBrush ;
struct TYPE_6__ {int /*<<< orphan*/  Context; } ;
typedef  TYPE_2__ uiAreaDrawParams ;

/* Variables and functions */
 int /*<<< orphan*/  crsourcergba (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 void* uiDrawLineJoinBevel ; 
 void* uiDrawLineJoinMiter ; 
 void* uiDrawLineJoinRound ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void drawCSSetLineJoin(uiAreaDrawParams *p)
{
	uiDrawBrush source;
	uiDrawStrokeParams sp;
	uiDrawPath *path;

	crsourcergba(&source, 0, 0, 0, 1);
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.MiterLimit = uiDrawDefaultMiterLimit;
	sp.Dashes = NULL;
	sp.NumDashes = 0;
	sp.DashPhase = 0;

	sp.Thickness = 40.96;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path, 76.8, 84.48);
	uiDrawPathLineTo(path, 76.8 + 51.2, 84.48 -51.2);
	uiDrawPathLineTo(path, 76.8 + 51.2 + 51.2, 84.48 - 51.2 + 51.2);
	uiDrawPathEnd(path);
	sp.Join = uiDrawLineJoinMiter;
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);

	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path, 76.8, 161.28);
	uiDrawPathLineTo(path, 76.8 + 51.2, 161.28 -51.2);
	uiDrawPathLineTo(path, 76.8 + 51.2 + 51.2, 161.28 - 51.2 + 51.2);
	uiDrawPathEnd(path);
	sp.Join = uiDrawLineJoinBevel;
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);

	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path, 76.8, 238.08);
	uiDrawPathLineTo(path, 76.8 + 51.2, 238.08 -51.2);
	uiDrawPathLineTo(path, 76.8 + 51.2 + 51.2, 238.08 - 51.2 + 51.2);
	uiDrawPathEnd(path);
	sp.Join = uiDrawLineJoinRound;
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);
}