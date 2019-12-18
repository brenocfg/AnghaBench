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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FLOAT_WORD (int,float) ; 
 float floorf (float) ; 

float
roundf(float x)
{
	float t;
	uint32_t hx;

	GET_FLOAT_WORD(hx, x);
	if ((hx & 0x7fffffff) == 0x7f800000)
		return (x + x);

	if (!(hx & 0x80000000)) {
		t = floorf(x);
		if (t - x <= -0.5F)
			t += 1;
		return (t);
	} else {
		t = floorf(-x);
		if (t + x <= -0.5F)
			t += 1;
		return (-t);
	}
}