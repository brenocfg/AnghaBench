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
struct TYPE_5__ {int Cap; int Join; int /*<<< orphan*/  DashPhase; int /*<<< orphan*/  NumDashes; int /*<<< orphan*/  Dashes; int /*<<< orphan*/  Thickness; int /*<<< orphan*/  MiterLimit; } ;
typedef  TYPE_1__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
struct TYPE_6__ {int /*<<< orphan*/  cr; } ;
typedef  TYPE_2__ uiDrawContext ;
typedef  int /*<<< orphan*/  uiDrawBrush ;
typedef  int /*<<< orphan*/  cairo_pattern_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_LINE_CAP_BUTT ; 
 int /*<<< orphan*/  CAIRO_LINE_CAP_ROUND ; 
 int /*<<< orphan*/  CAIRO_LINE_CAP_SQUARE ; 
 int /*<<< orphan*/  CAIRO_LINE_JOIN_BEVEL ; 
 int /*<<< orphan*/  CAIRO_LINE_JOIN_MITER ; 
 int /*<<< orphan*/  CAIRO_LINE_JOIN_ROUND ; 
 int /*<<< orphan*/  cairo_pattern_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_dash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_line_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_line_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_line_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_miter_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_stroke (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mkbrush (int /*<<< orphan*/ *) ; 
#define  uiDrawLineCapFlat 133 
#define  uiDrawLineCapRound 132 
#define  uiDrawLineCapSquare 131 
#define  uiDrawLineJoinBevel 130 
#define  uiDrawLineJoinMiter 129 
#define  uiDrawLineJoinRound 128 
 int /*<<< orphan*/  uiprivRunPath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void uiDrawStroke(uiDrawContext *c, uiDrawPath *path, uiDrawBrush *b, uiDrawStrokeParams *p)
{
	cairo_pattern_t *pat;

	uiprivRunPath(path, c->cr);
	pat = mkbrush(b);
	cairo_set_source(c->cr, pat);
	switch (p->Cap) {
	case uiDrawLineCapFlat:
		cairo_set_line_cap(c->cr, CAIRO_LINE_CAP_BUTT);
		break;
	case uiDrawLineCapRound:
		cairo_set_line_cap(c->cr, CAIRO_LINE_CAP_ROUND);
		break;
	case uiDrawLineCapSquare:
		cairo_set_line_cap(c->cr, CAIRO_LINE_CAP_SQUARE);
		break;
	}
	switch (p->Join) {
	case uiDrawLineJoinMiter:
		cairo_set_line_join(c->cr, CAIRO_LINE_JOIN_MITER);
		cairo_set_miter_limit(c->cr, p->MiterLimit);
		break;
	case uiDrawLineJoinRound:
		cairo_set_line_join(c->cr, CAIRO_LINE_JOIN_ROUND);
		break;
	case uiDrawLineJoinBevel:
		cairo_set_line_join(c->cr, CAIRO_LINE_JOIN_BEVEL);
		break;
	}
	cairo_set_line_width(c->cr, p->Thickness);
	cairo_set_dash(c->cr, p->Dashes, p->NumDashes, p->DashPhase);
	cairo_stroke(c->cr);
	cairo_pattern_destroy(pat);
}