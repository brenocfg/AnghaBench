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
 int /*<<< orphan*/  c2m (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_matrix_multiply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m2c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void uiDrawMatrixMultiply(uiDrawMatrix *dest, uiDrawMatrix *src)
{
	cairo_matrix_t c;
	cairo_matrix_t d;

	m2c(dest, &c);
	m2c(src, &d);
	cairo_matrix_multiply(&c, &c, &d);
	c2m(&c, dest);
}