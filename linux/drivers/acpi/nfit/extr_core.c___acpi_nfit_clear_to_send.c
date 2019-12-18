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
struct nvdimm_bus_descriptor {int dummy; } ;
struct nvdimm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct acpi_nfit_desc {TYPE_1__ dwork; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int ND_CMD_ARS_START ; 
 struct acpi_nfit_desc* to_acpi_desc (struct nvdimm_bus_descriptor*) ; 
 scalar_t__ work_busy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __acpi_nfit_clear_to_send(struct nvdimm_bus_descriptor *nd_desc,
		struct nvdimm *nvdimm, unsigned int cmd)
{
	struct acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

	if (nvdimm)
		return 0;
	if (cmd != ND_CMD_ARS_START)
		return 0;

	/*
	 * The kernel and userspace may race to initiate a scrub, but
	 * the scrub thread is prepared to lose that initial race.  It
	 * just needs guarantees that any ARS it initiates are not
	 * interrupted by any intervening start requests from userspace.
	 */
	if (work_busy(&acpi_desc->dwork.work))
		return -EBUSY;

	return 0;
}