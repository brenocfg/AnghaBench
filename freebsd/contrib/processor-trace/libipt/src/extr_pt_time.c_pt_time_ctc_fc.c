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
typedef  int uint32_t ;
struct pt_config {int cpuid_0x15_eax; int cpuid_0x15_ebx; } ;

/* Variables and functions */
 int pte_bad_config ; 
 int pte_internal ; 

__attribute__((used)) static int pt_time_ctc_fc(uint64_t *fc, uint64_t ctc,
			  const struct pt_config *config)
{
	uint32_t eax, ebx;

	if (!fc || !config)
		return -pte_internal;

	eax = config->cpuid_0x15_eax;
	ebx = config->cpuid_0x15_ebx;

	/* Neither multiply nor divide by zero. */
	if (!eax || !ebx)
		return -pte_bad_config;

	*fc = (ctc * ebx) / eax;
	return 0;
}