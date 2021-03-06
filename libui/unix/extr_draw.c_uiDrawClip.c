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
typedef  int /*<<< orphan*/  uiDrawPath ;
struct TYPE_3__ {int /*<<< orphan*/  cr; } ;
typedef  TYPE_1__ uiDrawContext ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FILL_RULE_EVEN_ODD ; 
 int /*<<< orphan*/  CAIRO_FILL_RULE_WINDING ; 
 int /*<<< orphan*/  cairo_clip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_fill_rule (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  uiDrawFillModeAlternate 129 
#define  uiDrawFillModeWinding 128 
 int uiprivPathFillMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiprivRunPath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void uiDrawClip(uiDrawContext *c, uiDrawPath *path)
{
	uiprivRunPath(path, c->cr);
	switch (uiprivPathFillMode(path)) {
	case uiDrawFillModeWinding:
		cairo_set_fill_rule(c->cr, CAIRO_FILL_RULE_WINDING);
		break;
	case uiDrawFillModeAlternate:
		cairo_set_fill_rule(c->cr, CAIRO_FILL_RULE_EVEN_ODD);
		break;
	}
	cairo_clip(c->cr);
}