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
 int /*<<< orphan*/  SET_FLOAT_WORD (float,int) ; 
 float expf (scalar_t__) ; 
 int k ; 
 scalar_t__ kln2 ; 

__attribute__((used)) static float
__frexp_expf(float x, int *expt)
{
	float exp_x;
	uint32_t hx;

	exp_x = expf(x - kln2);
	GET_FLOAT_WORD(hx, exp_x);
	*expt = (hx >> 23) - (0x7f + 127) + k;
	SET_FLOAT_WORD(exp_x, (hx & 0x7fffff) | ((0x7f + 127) << 23));
	return (exp_x);
}