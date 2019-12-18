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
typedef  int /*<<< orphan*/  uiDrawMatrix ;
struct TYPE_3__ {int /*<<< orphan*/  cr; } ;
typedef  TYPE_1__ uiDrawContext ;
typedef  int /*<<< orphan*/  cairo_matrix_t ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_transform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiprivM2C (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void uiDrawTransform(uiDrawContext *c, uiDrawMatrix *m)
{
	cairo_matrix_t cm;

	uiprivM2C(m, &cm);
	cairo_transform(c->cr, &cm);
}