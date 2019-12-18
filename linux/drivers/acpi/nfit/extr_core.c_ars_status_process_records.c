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
typedef  int u32 ;
struct nvdimm_bus {int dummy; } ;
struct nd_cmd_ars_status {int out_length; int num_records; TYPE_1__* records; } ;
struct nd_ars_record {int dummy; } ;
struct acpi_nfit_desc {int /*<<< orphan*/  dev; int /*<<< orphan*/  scrub_flags; struct nd_cmd_ars_status* ars_status; struct nvdimm_bus* nvdimm_bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  err_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARS_VALID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int nvdimm_bus_add_badrange (struct nvdimm_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ars_status_process_records(struct acpi_nfit_desc *acpi_desc)
{
	struct nvdimm_bus *nvdimm_bus = acpi_desc->nvdimm_bus;
	struct nd_cmd_ars_status *ars_status = acpi_desc->ars_status;
	int rc;
	u32 i;

	/*
	 * First record starts at 44 byte offset from the start of the
	 * payload.
	 */
	if (ars_status->out_length < 44)
		return 0;

	/*
	 * Ignore potentially stale results that are only refreshed
	 * after a start-ARS event.
	 */
	if (!test_and_clear_bit(ARS_VALID, &acpi_desc->scrub_flags)) {
		dev_dbg(acpi_desc->dev, "skip %d stale records\n",
				ars_status->num_records);
		return 0;
	}

	for (i = 0; i < ars_status->num_records; i++) {
		/* only process full records */
		if (ars_status->out_length
				< 44 + sizeof(struct nd_ars_record) * (i + 1))
			break;
		rc = nvdimm_bus_add_badrange(nvdimm_bus,
				ars_status->records[i].err_address,
				ars_status->records[i].length);
		if (rc)
			return rc;
	}
	if (i < ars_status->num_records)
		dev_warn(acpi_desc->dev, "detected truncated ars results\n");

	return 0;
}