#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_8__ {size_t count; TYPE_3__* ids; } ;
struct TYPE_6__ {int /*<<< orphan*/  string; } ;
struct TYPE_5__ {int /*<<< orphan*/  string; } ;
struct acpi_device_info {int valid; TYPE_4__ compatible_id_list; TYPE_2__ unique_id; TYPE_1__ hardware_id; int /*<<< orphan*/ * lowest_dstates; int /*<<< orphan*/ * highest_dstates; int /*<<< orphan*/  flags; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_7__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 size_t ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_device_info*) ; 
 int /*<<< orphan*/  ACPI_TO_POINTER (int /*<<< orphan*/ ) ; 
 int ACPI_VALID_CID ; 
 int ACPI_VALID_HID ; 
 int ACPI_VALID_UID ; 
 int /*<<< orphan*/  acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_object_info (int /*<<< orphan*/ ,struct acpi_device_info**) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,size_t,...) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 

void acpi_db_display_object_type(char *object_arg)
{
	acpi_size arg;
	acpi_handle handle;
	struct acpi_device_info *info;
	acpi_status status;
	u32 i;

	arg = strtoul(object_arg, NULL, 16);
	handle = ACPI_TO_POINTER(arg);

	status = acpi_get_object_info(handle, &info);
	if (ACPI_FAILURE(status)) {
		acpi_os_printf("Could not get object info, %s\n",
			       acpi_format_exception(status));
		return;
	}

	acpi_os_printf("ADR: %8.8X%8.8X, Flags: %X\n",
		       ACPI_FORMAT_UINT64(info->address), info->flags);

	acpi_os_printf("S1D-%2.2X S2D-%2.2X S3D-%2.2X S4D-%2.2X\n",
		       info->highest_dstates[0], info->highest_dstates[1],
		       info->highest_dstates[2], info->highest_dstates[3]);

	acpi_os_printf("S0W-%2.2X S1W-%2.2X S2W-%2.2X S3W-%2.2X S4W-%2.2X\n",
		       info->lowest_dstates[0], info->lowest_dstates[1],
		       info->lowest_dstates[2], info->lowest_dstates[3],
		       info->lowest_dstates[4]);

	if (info->valid & ACPI_VALID_HID) {
		acpi_os_printf("HID: %s\n", info->hardware_id.string);
	}

	if (info->valid & ACPI_VALID_UID) {
		acpi_os_printf("UID: %s\n", info->unique_id.string);
	}

	if (info->valid & ACPI_VALID_CID) {
		for (i = 0; i < info->compatible_id_list.count; i++) {
			acpi_os_printf("CID %u: %s\n", i,
				       info->compatible_id_list.ids[i].string);
		}
	}

	ACPI_FREE(info);
}