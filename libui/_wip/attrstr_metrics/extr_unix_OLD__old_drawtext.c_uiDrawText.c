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
typedef  int /*<<< orphan*/  uiDrawTextLayout ;
struct TYPE_3__ {int /*<<< orphan*/  cr; } ;
typedef  TYPE_1__ uiDrawContext ;
typedef  int /*<<< orphan*/  PangoLayout ;

/* Variables and functions */
 int /*<<< orphan*/ * pango_cairo_create_layout (int /*<<< orphan*/ ) ; 

void uiDrawText(uiDrawContext *c, double x, double y, uiDrawTextLayout *layout)
{
	PangoLayout *pl;

	pl = pango_cairo_create_layout(c->cr);
}