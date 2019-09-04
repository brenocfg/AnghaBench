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
typedef  int /*<<< orphan*/  uiDrawContext ;
struct TYPE_4__ {double R; double G; double B; double A; int /*<<< orphan*/  Type; } ;
typedef  TYPE_1__ uiDrawBrush ;
struct trect {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; scalar_t__ in; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiDrawBrushTypeSolid ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drawtrect(uiDrawContext *c, struct trect tr, double r, double g, double bl)
{
	uiDrawPath *p;
	uiDrawBrush b;

	memset(&b, 0, sizeof (uiDrawBrush));
	b.Type = uiDrawBrushTypeSolid;
	b.R = r;
	b.G = g;
	b.B = bl;
	b.A = 1.0;
	if (tr.in) {
		b.R += b.R * 0.75;
		b.G += b.G * 0.75;
		b.B += b.B * 0.75;
	}
	p = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(p,
		tr.left,
		tr.top,
		tr.right - tr.left,
		tr.bottom - tr.top);
	uiDrawPathEnd(p);
	uiDrawFill(c, p, &b);
	uiDrawFreePath(p);
}