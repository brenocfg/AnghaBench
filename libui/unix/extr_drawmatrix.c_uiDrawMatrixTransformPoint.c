#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uiDrawMatrix ;
typedef  int /*<<< orphan*/  cairo_matrix_t ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_matrix_transform_point (int /*<<< orphan*/ *,double*,double*) ; 
 int /*<<< orphan*/  m2c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void uiDrawMatrixTransformPoint(uiDrawMatrix *m, double *x, double *y)
{
	cairo_matrix_t c;

	m2c(m, &c);
	cairo_matrix_transform_point(&c, x, y);
}