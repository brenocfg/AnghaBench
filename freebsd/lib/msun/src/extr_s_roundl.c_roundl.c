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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTERI () ; 
 int /*<<< orphan*/  GET_LDBL_EXPSIGN (int,long double) ; 
 int /*<<< orphan*/  RETURNI (long double) ; 
 long double floorl (long double) ; 

long double
roundl(long double x)
{
	long double t;
	uint16_t hx;

	GET_LDBL_EXPSIGN(hx, x);
	if ((hx & 0x7fff) == 0x7fff)
		return (x + x);

	ENTERI();

	if (!(hx & 0x8000)) {
		t = floorl(x);
		if (t - x <= -0.5L)
			t += 1;
		RETURNI(t);
	} else {
		t = floorl(-x);
		if (t + x <= -0.5L)
			t += 1;
		RETURNI(-t);
	}
}