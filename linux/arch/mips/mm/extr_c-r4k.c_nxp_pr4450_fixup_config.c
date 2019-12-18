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
 int /*<<< orphan*/  NXP_BARRIER () ; 
 int _CACHE_SHIFT ; 
 int _page_cachable_default ; 
 unsigned long read_c0_config () ; 
 int /*<<< orphan*/  write_c0_config (unsigned long) ; 

__attribute__((used)) static void nxp_pr4450_fixup_config(void)
{
	unsigned long config0;

	config0 = read_c0_config();

	/* clear all three cache coherency fields */
	config0 &= ~(0x7 | (7 << 25) | (7 << 28));
	config0 |= (((_page_cachable_default >> _CACHE_SHIFT) <<  0) |
		    ((_page_cachable_default >> _CACHE_SHIFT) << 25) |
		    ((_page_cachable_default >> _CACHE_SHIFT) << 28));
	write_c0_config(config0);
	NXP_BARRIER();
}