#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct amd_northbridge {int dummy; } ;
struct TYPE_6__ {int num; int /*<<< orphan*/  flags; struct amd_northbridge* nb; } ;
struct TYPE_5__ {scalar_t__ x86_vendor; int x86; int x86_model; int x86_stepping; } ;
struct TYPE_4__ {struct pci_dev* link; struct pci_dev* misc; struct pci_dev* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_NB_GART ; 
 int /*<<< orphan*/  AMD_NB_L3_INDEX_DISABLE ; 
 int /*<<< orphan*/  AMD_NB_L3_PARTITIONING ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ X86_VENDOR_HYGON ; 
 scalar_t__ amd_gart_present () ; 
 struct pci_device_id* amd_nb_link_ids ; 
 struct pci_device_id* amd_nb_misc_ids ; 
 TYPE_3__ amd_northbridges ; 
 struct pci_device_id* amd_root_ids ; 
 TYPE_2__ boot_cpu_data ; 
 int /*<<< orphan*/  cpuid_edx (int) ; 
 struct pci_device_id* hygon_nb_link_ids ; 
 struct pci_device_id* hygon_nb_misc_ids ; 
 struct pci_device_id* hygon_root_ids ; 
 struct amd_northbridge* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct pci_dev* next_northbridge (struct pci_dev*,struct pci_device_id const*) ; 
 TYPE_1__* node_to_amd_nb (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

int amd_cache_northbridges(void)
{
	const struct pci_device_id *misc_ids = amd_nb_misc_ids;
	const struct pci_device_id *link_ids = amd_nb_link_ids;
	const struct pci_device_id *root_ids = amd_root_ids;
	struct pci_dev *root, *misc, *link;
	struct amd_northbridge *nb;
	u16 roots_per_misc = 0;
	u16 misc_count = 0;
	u16 root_count = 0;
	u16 i, j;

	if (amd_northbridges.num)
		return 0;

	if (boot_cpu_data.x86_vendor == X86_VENDOR_HYGON) {
		root_ids = hygon_root_ids;
		misc_ids = hygon_nb_misc_ids;
		link_ids = hygon_nb_link_ids;
	}

	misc = NULL;
	while ((misc = next_northbridge(misc, misc_ids)) != NULL)
		misc_count++;

	if (!misc_count)
		return -ENODEV;

	root = NULL;
	while ((root = next_northbridge(root, root_ids)) != NULL)
		root_count++;

	if (root_count) {
		roots_per_misc = root_count / misc_count;

		/*
		 * There should be _exactly_ N roots for each DF/SMN
		 * interface.
		 */
		if (!roots_per_misc || (root_count % roots_per_misc)) {
			pr_info("Unsupported AMD DF/PCI configuration found\n");
			return -ENODEV;
		}
	}

	nb = kcalloc(misc_count, sizeof(struct amd_northbridge), GFP_KERNEL);
	if (!nb)
		return -ENOMEM;

	amd_northbridges.nb = nb;
	amd_northbridges.num = misc_count;

	link = misc = root = NULL;
	for (i = 0; i < amd_northbridges.num; i++) {
		node_to_amd_nb(i)->root = root =
			next_northbridge(root, root_ids);
		node_to_amd_nb(i)->misc = misc =
			next_northbridge(misc, misc_ids);
		node_to_amd_nb(i)->link = link =
			next_northbridge(link, link_ids);

		/*
		 * If there are more PCI root devices than data fabric/
		 * system management network interfaces, then the (N)
		 * PCI roots per DF/SMN interface are functionally the
		 * same (for DF/SMN access) and N-1 are redundant.  N-1
		 * PCI roots should be skipped per DF/SMN interface so
		 * the following DF/SMN interfaces get mapped to
		 * correct PCI roots.
		 */
		for (j = 1; j < roots_per_misc; j++)
			root = next_northbridge(root, root_ids);
	}

	if (amd_gart_present())
		amd_northbridges.flags |= AMD_NB_GART;

	/*
	 * Check for L3 cache presence.
	 */
	if (!cpuid_edx(0x80000006))
		return 0;

	/*
	 * Some CPU families support L3 Cache Index Disable. There are some
	 * limitations because of E382 and E388 on family 0x10.
	 */
	if (boot_cpu_data.x86 == 0x10 &&
	    boot_cpu_data.x86_model >= 0x8 &&
	    (boot_cpu_data.x86_model > 0x9 ||
	     boot_cpu_data.x86_stepping >= 0x1))
		amd_northbridges.flags |= AMD_NB_L3_INDEX_DISABLE;

	if (boot_cpu_data.x86 == 0x15)
		amd_northbridges.flags |= AMD_NB_L3_INDEX_DISABLE;

	/* L3 cache partitioning is supported on family 0x15 */
	if (boot_cpu_data.x86 == 0x15)
		amd_northbridges.flags |= AMD_NB_L3_PARTITIONING;

	return 0;
}