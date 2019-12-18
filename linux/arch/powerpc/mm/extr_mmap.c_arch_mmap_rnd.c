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

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long get_random_long () ; 
 scalar_t__ is_32bit_task () ; 
 unsigned long mmap_rnd_bits ; 
 unsigned long mmap_rnd_compat_bits ; 

unsigned long arch_mmap_rnd(void)
{
	unsigned long shift, rnd;

	shift = mmap_rnd_bits;
#ifdef CONFIG_COMPAT
	if (is_32bit_task())
		shift = mmap_rnd_compat_bits;
#endif
	rnd = get_random_long() % (1ul << shift);

	return rnd << PAGE_SHIFT;
}