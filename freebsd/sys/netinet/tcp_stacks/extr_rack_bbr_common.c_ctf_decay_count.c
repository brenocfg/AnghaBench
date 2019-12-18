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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */

uint32_t 
ctf_decay_count(uint32_t count, uint32_t decay)
{
	/*
	 * Given a count, decay it by a set percentage. The
	 * percentage is in thousands i.e. 100% = 1000, 
	 * 19.3% = 193.
	 */
	uint64_t perc_count, decay_per;
	uint32_t decayed_count;
	if (decay > 1000) {
		/* We don't raise it */
		return (count);
	}
	perc_count = count;
	decay_per = decay;
	perc_count *= decay_per;
	perc_count /= 1000;
	/* 
	 * So now perc_count holds the 
	 * count decay value.
	 */
	decayed_count = count - (uint32_t)perc_count;
	return(decayed_count);
}