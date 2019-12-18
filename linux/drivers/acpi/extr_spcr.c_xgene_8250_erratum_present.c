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
struct TYPE_2__ {int oem_revision; int /*<<< orphan*/  oem_table_id; int /*<<< orphan*/  oem_id; } ;
struct acpi_table_spcr {scalar_t__ interface_type; TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ ACPI_DBG2_16550_COMPATIBLE ; 
 int /*<<< orphan*/  ACPI_OEM_ID_SIZE ; 
 int /*<<< orphan*/  ACPI_OEM_TABLE_ID_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool xgene_8250_erratum_present(struct acpi_table_spcr *tb)
{
	bool xgene_8250 = false;

	if (tb->interface_type != ACPI_DBG2_16550_COMPATIBLE)
		return false;

	if (memcmp(tb->header.oem_id, "APMC0D", ACPI_OEM_ID_SIZE) &&
	    memcmp(tb->header.oem_id, "HPE   ", ACPI_OEM_ID_SIZE))
		return false;

	if (!memcmp(tb->header.oem_table_id, "XGENESPC",
	    ACPI_OEM_TABLE_ID_SIZE) && tb->header.oem_revision == 0)
		xgene_8250 = true;

	if (!memcmp(tb->header.oem_table_id, "ProLiant",
	    ACPI_OEM_TABLE_ID_SIZE) && tb->header.oem_revision == 1)
		xgene_8250 = true;

	return xgene_8250;
}