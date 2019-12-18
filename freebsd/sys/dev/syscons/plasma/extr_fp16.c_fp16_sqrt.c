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
typedef  int fp16_t ;

/* Variables and functions */
 int flsl (int) ; 
 int fp16_div (int,int) ; 
 int fp16_mul (int,int) ; 
 int fp16_sub (int,int) ; 

fp16_t
fp16_sqrt(fp16_t x)
{
	fp16_t y, delta;
	signed int log2x;

	/* special case */
	if (x == 0)
		return (0);

	/* shift toward 0 by half the logarithm */
	log2x = flsl(x) - 1;
	if (log2x >= 16) {
		y = x >> (log2x - 16) / 2;
	} else {
#if 0
		y = x << (16 - log2x) / 2;
#else
		/* XXX for now, return 0 for anything < 1 */
		return (0);
#endif
	}
	while (y > 0) {
		/* delta = y^2 / 2y */
		delta = fp16_div(fp16_sub(fp16_mul(y, y), x), y * 2);
		if (delta == 0)
			break;
		y = fp16_sub(y, delta);
	}
	return (y);
}