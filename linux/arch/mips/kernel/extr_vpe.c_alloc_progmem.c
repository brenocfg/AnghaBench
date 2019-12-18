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
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_low_pfn ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned long) ; 
 void* pfn_to_kaddr (int /*<<< orphan*/ ) ; 

void *alloc_progmem(unsigned long len)
{
	void *addr;

#ifdef CONFIG_MIPS_VPE_LOADER_TOM
	/*
	 * This means you must tell Linux to use less memory than you
	 * physically have, for example by passing a mem= boot argument.
	 */
	addr = pfn_to_kaddr(max_low_pfn);
	memset(addr, 0, len);
#else
	/* simple grab some mem for now */
	addr = kzalloc(len, GFP_KERNEL);
#endif

	return addr;
}