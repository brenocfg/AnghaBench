#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ibft_kobject {TYPE_2__* header; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  oem_table_id; int /*<<< orphan*/  oem_id; int /*<<< orphan*/  signature; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  ACPI_OEM_ID_SIZE ; 
 int /*<<< orphan*/  ACPI_OEM_TABLE_ID_SIZE ; 
#define  ISCSI_BOOT_ACPITBL_OEM_ID 130 
#define  ISCSI_BOOT_ACPITBL_OEM_TABLE_ID 129 
#define  ISCSI_BOOT_ACPITBL_SIGNATURE 128 
 int /*<<< orphan*/  sprintf_string (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ibft_attr_show_acpitbl(void *data, int type, char *buf)
{
	struct ibft_kobject *entry = data;
	char *str = buf;

	switch (type) {
	case ISCSI_BOOT_ACPITBL_SIGNATURE:
		str += sprintf_string(str, ACPI_NAMESEG_SIZE,
				      entry->header->header.signature);
		break;
	case ISCSI_BOOT_ACPITBL_OEM_ID:
		str += sprintf_string(str, ACPI_OEM_ID_SIZE,
				      entry->header->header.oem_id);
		break;
	case ISCSI_BOOT_ACPITBL_OEM_TABLE_ID:
		str += sprintf_string(str, ACPI_OEM_TABLE_ID_SIZE,
				      entry->header->header.oem_table_id);
		break;
	default:
		break;
	}

	return str - buf;
}