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
 int RF_ALIGNMENT_LOG2 (int) ; 

uint32_t
rman_make_alignment_flags(uint32_t size)
{
	int i;

	/*
	 * Find the hightest bit set, and add one if more than one bit
	 * set.  We're effectively computing the ceil(log2(size)) here.
	 */
	for (i = 31; i > 0; i--)
		if ((1 << i) & size)
			break;
	if (~(1 << i) & size)
		i++;

	return(RF_ALIGNMENT_LOG2(i));
}