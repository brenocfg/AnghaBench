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
struct TYPE_5__ {int /*<<< orphan*/  M32; int /*<<< orphan*/  M31; int /*<<< orphan*/  M22; int /*<<< orphan*/  M21; int /*<<< orphan*/  M12; int /*<<< orphan*/  M11; } ;
typedef  TYPE_1__ uiDrawMatrix ;
struct TYPE_6__ {int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; int /*<<< orphan*/  yy; int /*<<< orphan*/  xy; int /*<<< orphan*/  yx; int /*<<< orphan*/  xx; } ;
typedef  TYPE_2__ cairo_matrix_t ;

/* Variables and functions */

__attribute__((used)) static void m2c(uiDrawMatrix *m, cairo_matrix_t *c)
{
	c->xx = m->M11;
	c->yx = m->M12;
	c->xy = m->M21;
	c->yy = m->M22;
	c->x0 = m->M31;
	c->y0 = m->M32;
}