#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_hwfns; } ;
struct TYPE_8__ {char* mfw_ver; char* stormfw_ver; int pci_func; int /*<<< orphan*/  pci_dev; scalar_t__* grcdump_size; TYPE_1__ cdev; int /*<<< orphan*/  flash_size; } ;
typedef  TYPE_2__ qlnx_host_t ;
struct TYPE_9__ {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  reg_dump_len; int /*<<< orphan*/  eeprom_dump_len; int /*<<< orphan*/  stormfw_version; int /*<<< orphan*/  mfw_version; int /*<<< orphan*/  drv_version; int /*<<< orphan*/  drv_name; } ;
typedef  TYPE_3__ qlnx_drvinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 char* qlnx_name_str ; 
 char* qlnx_ver_str ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 

__attribute__((used)) static int
qlnx_drv_info(qlnx_host_t *ha, qlnx_drvinfo_t *drv_info)
{
	int i;

	bzero(drv_info, sizeof(qlnx_drvinfo_t));

	snprintf(drv_info->drv_name, sizeof(drv_info->drv_name), "%s",
		qlnx_name_str);
	snprintf(drv_info->drv_version, sizeof(drv_info->drv_version), "%s",
		qlnx_ver_str);
	snprintf(drv_info->mfw_version, sizeof(drv_info->mfw_version), "%s",
		ha->mfw_ver);
	snprintf(drv_info->stormfw_version, sizeof(drv_info->stormfw_version),
		"%s", ha->stormfw_ver);

	drv_info->eeprom_dump_len = ha->flash_size;

	for (i = 0; i < ha->cdev.num_hwfns; i++) {
		drv_info->reg_dump_len += ha->grcdump_size[i]; 
	}

	snprintf(drv_info->bus_info, sizeof(drv_info->bus_info),
		"%d:%d:%d", pci_get_bus(ha->pci_dev),
		pci_get_slot(ha->pci_dev), ha->pci_func);

	return (0);
}