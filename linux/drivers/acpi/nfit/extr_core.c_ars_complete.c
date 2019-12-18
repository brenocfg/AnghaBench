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
struct nfit_spa {struct nd_region* nd_region; struct acpi_nfit_system_address* spa; } ;
struct nd_region {int dummy; } ;
struct nd_cmd_ars_status {scalar_t__ address; scalar_t__ length; } ;
struct device {int dummy; } ;
struct acpi_nfit_system_address {scalar_t__ address; scalar_t__ length; int /*<<< orphan*/  range_index; } ;
struct acpi_nfit_desc {struct device* dev; struct nfit_spa* scrub_spa; int /*<<< orphan*/  init_mutex; struct nd_cmd_ars_status* ars_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVDIMM_REVALIDATE_POISON ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct device* nd_region_dev (struct nd_region*) ; 
 int /*<<< orphan*/  nvdimm_region_notify (struct nd_region*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ars_complete(struct acpi_nfit_desc *acpi_desc,
		struct nfit_spa *nfit_spa)
{
	struct nd_cmd_ars_status *ars_status = acpi_desc->ars_status;
	struct acpi_nfit_system_address *spa = nfit_spa->spa;
	struct nd_region *nd_region = nfit_spa->nd_region;
	struct device *dev;

	lockdep_assert_held(&acpi_desc->init_mutex);
	/*
	 * Only advance the ARS state for ARS runs initiated by the
	 * kernel, ignore ARS results from BIOS initiated runs for scrub
	 * completion tracking.
	 */
	if (acpi_desc->scrub_spa != nfit_spa)
		return;

	if ((ars_status->address >= spa->address && ars_status->address
				< spa->address + spa->length)
			|| (ars_status->address < spa->address)) {
		/*
		 * Assume that if a scrub starts at an offset from the
		 * start of nfit_spa that we are in the continuation
		 * case.
		 *
		 * Otherwise, if the scrub covers the spa range, mark
		 * any pending request complete.
		 */
		if (ars_status->address + ars_status->length
				>= spa->address + spa->length)
				/* complete */;
		else
			return;
	} else
		return;

	acpi_desc->scrub_spa = NULL;
	if (nd_region) {
		dev = nd_region_dev(nd_region);
		nvdimm_region_notify(nd_region, NVDIMM_REVALIDATE_POISON);
	} else
		dev = acpi_desc->dev;
	dev_dbg(dev, "ARS: range %d complete\n", spa->range_index);
}