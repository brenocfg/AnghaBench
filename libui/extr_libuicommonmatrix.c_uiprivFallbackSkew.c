#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double M12; double M21; double M31; double M32; } ;
typedef  TYPE_1__ uiDrawMatrix ;

/* Variables and functions */
 double tan (double) ; 
 int /*<<< orphan*/  uiDrawMatrixMultiply (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  uiDrawMatrixSetIdentity (TYPE_1__*) ; 

void uiprivFallbackSkew(uiDrawMatrix *m, double x, double y, double xamount, double yamount)
{
	uiDrawMatrix n;

	uiDrawMatrixSetIdentity(&n);
	// TODO explain this
	n.M12 = tan(yamount);
	n.M21 = tan(xamount);
	n.M31 = -y * tan(xamount);
	n.M32 = -x * tan(yamount);
	uiDrawMatrixMultiply(m, &n);
}