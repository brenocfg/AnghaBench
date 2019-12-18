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
struct TYPE_4__ {scalar_t__ M32; scalar_t__ M31; } ;
typedef  TYPE_1__ uiDrawMatrix ;

/* Variables and functions */
 int /*<<< orphan*/  uiDrawMatrixTransformPoint (TYPE_1__*,double*,double*) ; 

void uiprivFallbackTransformSize(uiDrawMatrix *m, double *x, double *y)
{
	uiDrawMatrix m2;

	m2 = *m;
	m2.M31 = 0;
	m2.M32 = 0;
	uiDrawMatrixTransformPoint(&m2, x, y);
}