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
 unsigned long DEFAULT_MAP_WINDOW ; 
 unsigned long TASK_SIZE ; 

bool mmap_address_hint_valid(unsigned long addr, unsigned long len)
{
	if (TASK_SIZE - len < addr)
		return false;

	return (addr > DEFAULT_MAP_WINDOW) == (addr + len > DEFAULT_MAP_WINDOW);
}