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
 scalar_t__ CAIRO_STATUS_SUCCESS ; 
 int /*<<< orphan*/  c2m (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cairo_matrix_invert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m2c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int uiDrawMatrixInvert(uiDrawMatrix *m)
{
	cairo_matrix_t c;

	m2c(m, &c);
	if (cairo_matrix_invert(&c) != CAIRO_STATUS_SUCCESS)
		return 0;
	c2m(&c, m);
	return 1;
}