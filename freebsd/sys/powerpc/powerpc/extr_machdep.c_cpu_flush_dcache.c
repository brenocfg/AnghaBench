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
typedef  int register_t ;

/* Variables and functions */
 int cacheline_size ; 
 size_t roundup2 (size_t,int) ; 

void
cpu_flush_dcache(void *ptr, size_t len)
{
	register_t addr, off;

	/*
	 * Align the address to a cacheline and adjust the length
	 * accordingly. Then round the length to a multiple of the
	 * cacheline for easy looping.
	 */
	addr = (uintptr_t)ptr;
	off = addr & (cacheline_size - 1);
	addr -= off;
	len = roundup2(len + off, cacheline_size);

	while (len > 0) {
		__asm __volatile ("dcbf 0,%0" :: "r"(addr));
		__asm __volatile ("sync");
		addr += cacheline_size;
		len -= cacheline_size;
	}
}