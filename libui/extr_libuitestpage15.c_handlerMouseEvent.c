#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int Down; int /*<<< orphan*/  AreaHeight; int /*<<< orphan*/  AreaWidth; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_12__ uiAreaMouseEvent ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
typedef  int /*<<< orphan*/  uiArea ;
struct TYPE_15__ {scalar_t__ in; } ;
struct TYPE_14__ {scalar_t__ in; } ;
struct TYPE_25__ {scalar_t__ in; } ;
struct TYPE_24__ {scalar_t__ in; } ;
struct TYPE_23__ {scalar_t__ in; } ;
struct TYPE_22__ {scalar_t__ in; } ;
struct TYPE_21__ {scalar_t__ in; } ;
struct TYPE_20__ {scalar_t__ in; } ;
struct TYPE_19__ {scalar_t__ in; } ;
struct TYPE_18__ {scalar_t__ in; } ;
struct TYPE_17__ {scalar_t__ in; } ;
struct tareas {TYPE_11__ close; TYPE_10__ bottomrightresize; TYPE_9__ bottomleftresize; TYPE_8__ toprightresize; TYPE_7__ topleftresize; TYPE_6__ bottomresize; TYPE_5__ rightresize; TYPE_4__ topresize; TYPE_3__ leftresize; TYPE_2__ alsomove; TYPE_1__ move; } ;

/* Variables and functions */
 int /*<<< orphan*/  filltareas (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tareas*) ; 
 int /*<<< orphan*/  lastx ; 
 int /*<<< orphan*/  lasty ; 
 int /*<<< orphan*/  uiAreaBeginUserWindowMove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiAreaBeginUserWindowResize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiAreaQueueRedrawAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiWindowResizeEdgeBottom ; 
 int /*<<< orphan*/  uiWindowResizeEdgeBottomLeft ; 
 int /*<<< orphan*/  uiWindowResizeEdgeBottomRight ; 
 int /*<<< orphan*/  uiWindowResizeEdgeLeft ; 
 int /*<<< orphan*/  uiWindowResizeEdgeRight ; 
 int /*<<< orphan*/  uiWindowResizeEdgeTop ; 
 int /*<<< orphan*/  uiWindowResizeEdgeTopLeft ; 
 int /*<<< orphan*/  uiWindowResizeEdgeTopRight ; 

__attribute__((used)) static void handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e)
{
	struct tareas ta;

	lastx = e->X;
	lasty = e->Y;
	filltareas(e->AreaWidth, e->AreaHeight, &ta);
	// redraw our highlighted rect
	uiAreaQueueRedrawAll(area);
	if (e->Down != 1)
		return;
	if (ta.move.in || ta.alsomove.in) {
		uiAreaBeginUserWindowMove(area);
		return;
	}
#define resize(cond, edge) if (cond) { uiAreaBeginUserWindowResize(area, edge); return; }
	resize(ta.leftresize.in, uiWindowResizeEdgeLeft)
	resize(ta.topresize.in, uiWindowResizeEdgeTop)
	resize(ta.rightresize.in, uiWindowResizeEdgeRight)
	resize(ta.bottomresize.in, uiWindowResizeEdgeBottom)
	resize(ta.topleftresize.in, uiWindowResizeEdgeTopLeft)
	resize(ta.toprightresize.in, uiWindowResizeEdgeTopRight)
	resize(ta.bottomleftresize.in, uiWindowResizeEdgeBottomLeft)
	resize(ta.bottomrightresize.in, uiWindowResizeEdgeBottomRight)
	if (ta.close.in) {
		// TODO
		return;
	}
}