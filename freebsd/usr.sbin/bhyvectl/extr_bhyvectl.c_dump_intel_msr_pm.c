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
typedef  int uint32_t ;

/* Variables and functions */
 int MSR_AMD6TH_START ; 
 int /*<<< orphan*/  print_msr_pm (int,int,int,int) ; 

__attribute__((used)) static void
dump_intel_msr_pm(const char *bitmap, int vcpu)
{
	int byte, bit, readable, writeable;
	uint32_t msr;

	for (msr = 0; msr < 0x2000; msr++) {
		byte = msr / 8;
		bit = msr & 0x7;

		/* Look at MSRs in the range 0x00000000 to 0x00001FFF */
		readable = (bitmap[byte] & (1 << bit)) ? 0 : 1;
		writeable = (bitmap[2048 + byte] & (1 << bit)) ?  0 : 1;
		print_msr_pm(msr, vcpu, readable, writeable);

		/* Look at MSRs in the range 0xC0000000 to 0xC0001FFF */
		byte += 1024;
		readable = (bitmap[byte] & (1 << bit)) ? 0 : 1;
		writeable = (bitmap[2048 + byte] & (1 << bit)) ?  0 : 1;
		print_msr_pm(msr + MSR_AMD6TH_START, vcpu, readable,
				writeable);
	}
}