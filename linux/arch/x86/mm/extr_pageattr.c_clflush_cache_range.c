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
 int /*<<< orphan*/  clflush_cache_range_opt (void*,unsigned int) ; 
 int /*<<< orphan*/  mb () ; 

void clflush_cache_range(void *vaddr, unsigned int size)
{
	mb();
	clflush_cache_range_opt(vaddr, size);
	mb();
}