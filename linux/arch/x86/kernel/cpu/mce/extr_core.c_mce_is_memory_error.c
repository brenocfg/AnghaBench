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
struct mce {scalar_t__ cpuvendor; int status; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ X86_VENDOR_AMD ; 
 scalar_t__ X86_VENDOR_HYGON ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 int amd_mce_is_memory_error (struct mce*) ; 

bool mce_is_memory_error(struct mce *m)
{
	if (m->cpuvendor == X86_VENDOR_AMD ||
	    m->cpuvendor == X86_VENDOR_HYGON) {
		return amd_mce_is_memory_error(m);
	} else if (m->cpuvendor == X86_VENDOR_INTEL) {
		/*
		 * Intel SDM Volume 3B - 15.9.2 Compound Error Codes
		 *
		 * Bit 7 of the MCACOD field of IA32_MCi_STATUS is used for
		 * indicating a memory error. Bit 8 is used for indicating a
		 * cache hierarchy error. The combination of bit 2 and bit 3
		 * is used for indicating a `generic' cache hierarchy error
		 * But we can't just blindly check the above bits, because if
		 * bit 11 is set, then it is a bus/interconnect error - and
		 * either way the above bits just gives more detail on what
		 * bus/interconnect error happened. Note that bit 12 can be
		 * ignored, as it's the "filter" bit.
		 */
		return (m->status & 0xef80) == BIT(7) ||
		       (m->status & 0xef00) == BIT(8) ||
		       (m->status & 0xeffc) == 0xc;
	}

	return false;
}