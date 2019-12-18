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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  MSR_BIOS_SIGN ; 
 int /*<<< orphan*/  MSR_BIOS_UPDT_TRIG ; 
 int /*<<< orphan*/  do_cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsr_safe (int /*<<< orphan*/ ,int) ; 

int
ucode_intel_load(void *data, bool unsafe, uint64_t *nrevp, uint64_t *orevp)
{
	uint64_t nrev, orev;
	uint32_t cpuid[4];

	orev = rdmsr(MSR_BIOS_SIGN) >> 32;

	/*
	 * Perform update.  Flush caches first to work around seemingly
	 * undocumented errata applying to some Broadwell CPUs.
	 */
	wbinvd();
	if (unsafe)
		wrmsr_safe(MSR_BIOS_UPDT_TRIG, (uint64_t)(uintptr_t)data);
	else
		wrmsr(MSR_BIOS_UPDT_TRIG, (uint64_t)(uintptr_t)data);
	wrmsr(MSR_BIOS_SIGN, 0);

	/*
	 * Serialize instruction flow.
	 */
	do_cpuid(0, cpuid);

	/*
	 * Verify that the microcode revision changed.
	 */
	nrev = rdmsr(MSR_BIOS_SIGN) >> 32;
	if (nrevp != NULL)
		*nrevp = nrev;
	if (orevp != NULL)
		*orevp = orev;
	if (nrev <= orev)
		return (EEXIST);
	return (0);
}