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
typedef  int u32 ;

/* Variables and functions */
#define  VMWARE_BACKDOOR_PMC_APPARENT_TIME 130 
#define  VMWARE_BACKDOOR_PMC_HOST_TSC 129 
#define  VMWARE_BACKDOOR_PMC_REAL_TIME 128 

bool is_vmware_backdoor_pmc(u32 pmc_idx)
{
	switch (pmc_idx) {
	case VMWARE_BACKDOOR_PMC_HOST_TSC:
	case VMWARE_BACKDOOR_PMC_REAL_TIME:
	case VMWARE_BACKDOOR_PMC_APPARENT_TIME:
		return true;
	}
	return false;
}