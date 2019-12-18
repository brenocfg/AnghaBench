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
struct mem_ctl_info {int mtype_cap; int /*<<< orphan*/  get_sdram_scrub_rate; int /*<<< orphan*/  set_sdram_scrub_rate; int /*<<< orphan*/ * ctl_page_to_phys; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  mod_name; int /*<<< orphan*/  edac_cap; int /*<<< orphan*/  edac_ctl_cap; struct amd64_pvt* pvt_info; } ;
struct amd64_pvt {int nbcap; int /*<<< orphan*/  F3; scalar_t__ umc; } ;
struct amd64_family_type {int /*<<< orphan*/  ctl_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_FLAG_NONE ; 
 int /*<<< orphan*/  EDAC_FLAG_S4ECD4ED ; 
 int /*<<< orphan*/  EDAC_FLAG_SECDED ; 
 int /*<<< orphan*/  EDAC_MOD_STR ; 
 int MEM_FLAG_DDR2 ; 
 int MEM_FLAG_RDDR2 ; 
 int NBCAP_CHIPKILL ; 
 int NBCAP_SECDED ; 
 int /*<<< orphan*/  determine_edac_cap (struct amd64_pvt*) ; 
 int /*<<< orphan*/  f17h_determine_edac_ctl_cap (struct mem_ctl_info*,struct amd64_pvt*) ; 
 int /*<<< orphan*/  get_scrub_rate ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_scrub_rate ; 

__attribute__((used)) static void setup_mci_misc_attrs(struct mem_ctl_info *mci,
				 struct amd64_family_type *fam)
{
	struct amd64_pvt *pvt = mci->pvt_info;

	mci->mtype_cap		= MEM_FLAG_DDR2 | MEM_FLAG_RDDR2;
	mci->edac_ctl_cap	= EDAC_FLAG_NONE;

	if (pvt->umc) {
		f17h_determine_edac_ctl_cap(mci, pvt);
	} else {
		if (pvt->nbcap & NBCAP_SECDED)
			mci->edac_ctl_cap |= EDAC_FLAG_SECDED;

		if (pvt->nbcap & NBCAP_CHIPKILL)
			mci->edac_ctl_cap |= EDAC_FLAG_S4ECD4ED;
	}

	mci->edac_cap		= determine_edac_cap(pvt);
	mci->mod_name		= EDAC_MOD_STR;
	mci->ctl_name		= fam->ctl_name;
	mci->dev_name		= pci_name(pvt->F3);
	mci->ctl_page_to_phys	= NULL;

	/* memory scrubber interface */
	mci->set_sdram_scrub_rate = set_scrub_rate;
	mci->get_sdram_scrub_rate = get_scrub_rate;
}