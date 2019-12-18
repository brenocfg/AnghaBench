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
struct TYPE_5__ {int /*<<< orphan*/  layout; } ;
typedef  TYPE_1__ uiDrawTextLayout ;
struct TYPE_6__ {int /*<<< orphan*/  cr; } ;
typedef  TYPE_2__ uiDrawContext ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  cairo_set_source_rgb (int /*<<< orphan*/ ,double,double,double) ; 
 int /*<<< orphan*/  pango_cairo_show_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void uiDrawText(uiDrawContext *c, uiDrawTextLayout *tl, double x, double y)
{
	// TODO have an implicit save/restore on each drawing functions instead? and is this correct?
	cairo_set_source_rgb(c->cr, 0.0, 0.0, 0.0);
	cairo_move_to(c->cr, x, y);
	pango_cairo_show_layout(c->cr, tl->layout);
}