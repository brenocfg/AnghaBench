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
 unsigned int PAGE_SHIFT ; 
 int PTRS_PER_PTE ; 
 int get_random_int () ; 

__attribute__((used)) static unsigned long vdso_addr(unsigned long start, unsigned int len)
{
	unsigned int offset;

	/* This loses some more bits than a modulo, but is cheaper */
	offset = get_random_int() & (PTRS_PER_PTE - 1);
	return start + (offset << PAGE_SHIFT);
}