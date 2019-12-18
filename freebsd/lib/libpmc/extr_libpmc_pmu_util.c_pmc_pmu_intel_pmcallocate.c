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
struct pmu_event_desc {int ped_umask; int ped_event; scalar_t__ ped_inv; scalar_t__ ped_any; scalar_t__ ped_edge; int /*<<< orphan*/  ped_offcore_rsp; int /*<<< orphan*/  ped_cmask; } ;
struct pmc_md_iap_op_pmcallocate {int pm_iap_config; int /*<<< orphan*/  pm_iap_rsp; } ;
struct TYPE_2__ {struct pmc_md_iap_op_pmcallocate pm_iap; } ;
struct pmc_op_pmcallocate {int pm_caps; int /*<<< orphan*/  pm_class; TYPE_1__ pm_md; } ;

/* Variables and functions */
 int IAP_ANY ; 
 int IAP_CMASK (int /*<<< orphan*/ ) ; 
 int IAP_EDGE ; 
 int IAP_EVSEL (int) ; 
 int IAP_INT ; 
 int IAP_OS ; 
 int IAP_UMASK (int) ; 
 int IAP_USR ; 
 int PMC_CAP_INTERRUPT ; 
 int PMC_CAP_QUALIFIER ; 
 int PMC_CAP_SYSTEM ; 
 int PMC_CAP_USER ; 
 int /*<<< orphan*/  PMC_CLASS_IAF ; 
 int /*<<< orphan*/  PMC_CLASS_IAP ; 
 int /*<<< orphan*/  PMC_CLASS_UCP ; 
 char const* strcasestr (char const*,char*) ; 

__attribute__((used)) static int
pmc_pmu_intel_pmcallocate(const char *event_name, struct pmc_op_pmcallocate *pm,
	struct pmu_event_desc *ped)
{
	struct pmc_md_iap_op_pmcallocate *iap;
	int isfixed;

	isfixed = 0;
	iap = &pm->pm_md.pm_iap;
	if (strcasestr(event_name, "UNC_") == event_name ||
	    strcasestr(event_name, "uncore") != NULL) {
		pm->pm_class = PMC_CLASS_UCP;
		pm->pm_caps |= PMC_CAP_QUALIFIER;
	} else if ((ped->ped_umask == -1) ||
	    (ped->ped_event == 0x0 && ped->ped_umask == 0x3)) {
		pm->pm_class = PMC_CLASS_IAF;
	} else {
		pm->pm_class = PMC_CLASS_IAP;
		pm->pm_caps |= PMC_CAP_QUALIFIER;
	}
	iap->pm_iap_config |= IAP_EVSEL(ped->ped_event);
	if (ped->ped_umask > 0)
		iap->pm_iap_config |= IAP_UMASK(ped->ped_umask);
	iap->pm_iap_config |= IAP_CMASK(ped->ped_cmask);
	iap->pm_iap_rsp = ped->ped_offcore_rsp;

	if ((pm->pm_caps & (PMC_CAP_USER|PMC_CAP_SYSTEM)) == 0 ||
		(pm->pm_caps & (PMC_CAP_USER|PMC_CAP_SYSTEM)) ==
		(PMC_CAP_USER|PMC_CAP_SYSTEM))
		iap->pm_iap_config |= (IAP_USR | IAP_OS);
	else if (pm->pm_caps & PMC_CAP_USER)
		iap->pm_iap_config |= IAP_USR;
	else if (pm->pm_caps & PMC_CAP_SYSTEM)
		iap->pm_iap_config |= IAP_OS;
	if (ped->ped_edge)
		iap->pm_iap_config |= IAP_EDGE;
	if (ped->ped_any)
		iap->pm_iap_config |= IAP_ANY;
	if (ped->ped_inv)
		iap->pm_iap_config |= IAP_EDGE;
	if (pm->pm_caps & PMC_CAP_INTERRUPT)
		iap->pm_iap_config |= IAP_INT;
	return (0);
}