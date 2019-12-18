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
 unsigned long CACHE_PHYSADDR_MASK ; 
 unsigned long SH_CACHE_ASSOC ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,unsigned long) ; 

__attribute__((used)) static void sh2a_invalidate_line(unsigned long cache_addr, unsigned long v)
{
	/* Set associative bit to hit all ways */
	unsigned long addr = (v & 0x000007f0) | SH_CACHE_ASSOC;
	__raw_writel((addr & CACHE_PHYSADDR_MASK), cache_addr | addr);
}