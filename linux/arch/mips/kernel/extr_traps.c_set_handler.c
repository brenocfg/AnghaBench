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
 scalar_t__ ebase ; 
 int /*<<< orphan*/  local_flush_icache_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 

void set_handler(unsigned long offset, void *addr, unsigned long size)
{
#ifdef CONFIG_CPU_MICROMIPS
	memcpy((void *)(ebase + offset), ((unsigned char *)addr - 1), size);
#else
	memcpy((void *)(ebase + offset), addr, size);
#endif
	local_flush_icache_range(ebase + offset, ebase + offset + size);
}