#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiDrawPath ;
typedef  int /*<<< orphan*/  uiDrawBrush ;
struct TYPE_4__ {int /*<<< orphan*/  Context; } ;
typedef  TYPE_1__ uiAreaDrawParams ;

/* Variables and functions */
 int /*<<< orphan*/  cgaddrect (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  crsourcergba (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,double) ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drawQ2DCreateWindowGC(uiAreaDrawParams *p)
{
	uiDrawPath *path;
	uiDrawBrush brush;

	crsourcergba(&brush, 1, 0, 0, 1);
	path = uiDrawNewPath(uiDrawFillModeWinding);
	cgaddrect(path, p, 0, 0, 200, 100);
	uiDrawPathEnd(path);
	uiDrawFill(p->Context, path, &brush);
	uiDrawFreePath(path);

	crsourcergba(&brush, 0, 0, 1, .5);
	path = uiDrawNewPath(uiDrawFillModeWinding);
	cgaddrect(path, p, 0, 0, 100, 200);
	uiDrawPathEnd(path);
	uiDrawFill(p->Context, path, &brush);
	uiDrawFreePath(path);
}