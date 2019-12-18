#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int family; scalar_t__ model; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_X86_64 ; 
 int /*<<< orphan*/  CONFIG_X86_PAE ; 
 scalar_t__ INTEL_FAM6_XEON_PHI_KNL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 TYPE_1__ cpu ; 
 int /*<<< orphan*/  is_intel () ; 
 int /*<<< orphan*/  puts (char*) ; 

int check_knl_erratum(void)
{
	/*
	 * First check for the affected model/family:
	 */
	if (!is_intel() ||
	    cpu.family != 6 ||
	    cpu.model != INTEL_FAM6_XEON_PHI_KNL)
		return 0;

	/*
	 * This erratum affects the Accessed/Dirty bits, and can
	 * cause stray bits to be set in !Present PTEs.  We have
	 * enough bits in our 64-bit PTEs (which we have on real
	 * 64-bit mode or PAE) to avoid using these troublesome
	 * bits.  But, we do not have enough space in our 32-bit
	 * PTEs.  So, refuse to run on 32-bit non-PAE kernels.
	 */
	if (IS_ENABLED(CONFIG_X86_64) || IS_ENABLED(CONFIG_X86_PAE))
		return 0;

	puts("This 32-bit kernel can not run on this Xeon Phi x200\n"
	     "processor due to a processor erratum.  Use a 64-bit\n"
	     "kernel, or enable PAE in this 32-bit kernel.\n\n");

	return -1;
}