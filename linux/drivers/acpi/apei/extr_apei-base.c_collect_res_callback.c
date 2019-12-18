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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct apei_resources {int /*<<< orphan*/  ioport; int /*<<< orphan*/  iomem; } ;
struct apei_exec_context {TYPE_1__* ins_table; } ;
struct acpi_generic_address {int space_id; } ;
struct acpi_whea_header {size_t instruction; struct acpi_generic_address register_region; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
#define  ACPI_ADR_SPACE_SYSTEM_IO 129 
#define  ACPI_ADR_SPACE_SYSTEM_MEMORY 128 
 int APEI_EXEC_INS_ACCESS_REGISTER ; 
 int EINVAL ; 
 int apei_check_gar (struct acpi_generic_address*,int /*<<< orphan*/ *,int*) ; 
 int apei_res_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int collect_res_callback(struct apei_exec_context *ctx,
				struct acpi_whea_header *entry,
				void *data)
{
	struct apei_resources *resources = data;
	struct acpi_generic_address *reg = &entry->register_region;
	u8 ins = entry->instruction;
	u32 access_bit_width;
	u64 paddr;
	int rc;

	if (!(ctx->ins_table[ins].flags & APEI_EXEC_INS_ACCESS_REGISTER))
		return 0;

	rc = apei_check_gar(reg, &paddr, &access_bit_width);
	if (rc)
		return rc;

	switch (reg->space_id) {
	case ACPI_ADR_SPACE_SYSTEM_MEMORY:
		return apei_res_add(&resources->iomem, paddr,
				    access_bit_width / 8);
	case ACPI_ADR_SPACE_SYSTEM_IO:
		return apei_res_add(&resources->ioport, paddr,
				    access_bit_width / 8);
	default:
		return -EINVAL;
	}
}