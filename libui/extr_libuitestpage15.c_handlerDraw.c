#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiAreaHandler ;
struct TYPE_3__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  AreaHeight; int /*<<< orphan*/  AreaWidth; } ;
typedef  TYPE_1__ uiAreaDrawParams ;
typedef  int /*<<< orphan*/  uiArea ;
struct tareas {int /*<<< orphan*/  close; int /*<<< orphan*/  bottomrightresize; int /*<<< orphan*/  bottomleftresize; int /*<<< orphan*/  toprightresize; int /*<<< orphan*/  topleftresize; int /*<<< orphan*/  bottomresize; int /*<<< orphan*/  rightresize; int /*<<< orphan*/  topresize; int /*<<< orphan*/  leftresize; int /*<<< orphan*/  alsomove; int /*<<< orphan*/  move; } ;

/* Variables and functions */
 int /*<<< orphan*/  drawtrect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double) ; 
 int /*<<< orphan*/  filltareas (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tareas*) ; 

__attribute__((used)) static void handlerDraw(uiAreaHandler *a, uiArea *area, uiAreaDrawParams *p)
{
	struct tareas ta;

	filltareas(p->AreaWidth, p->AreaHeight, &ta);
	drawtrect(p->Context, ta.move, 0, 0.5, 0);
	drawtrect(p->Context, ta.alsomove, 0, 0.5, 0);
	drawtrect(p->Context, ta.leftresize, 0, 0, 0.5);
	drawtrect(p->Context, ta.topresize, 0, 0, 0.5);
	drawtrect(p->Context, ta.rightresize, 0, 0, 0.5);
	drawtrect(p->Context, ta.bottomresize, 0, 0, 0.5);
	drawtrect(p->Context, ta.topleftresize, 0, 0.5, 0.5);
	drawtrect(p->Context, ta.toprightresize, 0, 0.5, 0.5);
	drawtrect(p->Context, ta.bottomleftresize, 0, 0.5, 0.5);
	drawtrect(p->Context, ta.bottomrightresize, 0, 0.5, 0.5);
	drawtrect(p->Context, ta.close, 0.5, 0, 0);

	// TODO add current position prints here
}