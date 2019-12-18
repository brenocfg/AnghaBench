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
struct TYPE_2__ {struct ena_admin_host_info* host_info; } ;
struct ena_com_dev {TYPE_1__ host_attr; } ;
struct ena_admin_host_info {uintptr_t bdf; int kernel_ver; int driver_version; int /*<<< orphan*/  num_cpus; int /*<<< orphan*/  os_dist_str; scalar_t__ os_dist; int /*<<< orphan*/  kernel_ver_str; int /*<<< orphan*/  os_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DRV_MODULE_VER_MAJOR ; 
 int DRV_MODULE_VER_MINOR ; 
 int DRV_MODULE_VER_SUBMINOR ; 
 int ENA_ADMIN_HOST_INFO_MINOR_SHIFT ; 
 int ENA_ADMIN_HOST_INFO_SUB_MINOR_SHIFT ; 
 int /*<<< orphan*/  ENA_ADMIN_OS_FREEBSD ; 
 int /*<<< orphan*/  ENA_ALERT ; 
 int /*<<< orphan*/  ENA_WARNING ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PCI_ID_RID ; 
 int ena_com_allocate_host_info (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_delete_host_info (struct ena_com_dev*) ; 
 int ena_com_set_host_attributes (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_ncpus ; 
 int osreldate ; 
 int /*<<< orphan*/  osrelease ; 
 scalar_t__ pci_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
ena_config_host_info(struct ena_com_dev *ena_dev, device_t dev)
{
	struct ena_admin_host_info *host_info;
	uintptr_t rid;
	int rc;

	/* Allocate only the host info */
	rc = ena_com_allocate_host_info(ena_dev);
	if (unlikely(rc != 0)) {
		ena_trace(ENA_ALERT, "Cannot allocate host info\n");
		return;
	}

	host_info = ena_dev->host_attr.host_info;

	if (pci_get_id(dev, PCI_ID_RID, &rid) == 0)
		host_info->bdf = rid;
	host_info->os_type = ENA_ADMIN_OS_FREEBSD;
	host_info->kernel_ver = osreldate;

	sprintf(host_info->kernel_ver_str, "%d", osreldate);
	host_info->os_dist = 0;
	strncpy(host_info->os_dist_str, osrelease,
	    sizeof(host_info->os_dist_str) - 1);

	host_info->driver_version =
		(DRV_MODULE_VER_MAJOR) |
		(DRV_MODULE_VER_MINOR << ENA_ADMIN_HOST_INFO_MINOR_SHIFT) |
		(DRV_MODULE_VER_SUBMINOR << ENA_ADMIN_HOST_INFO_SUB_MINOR_SHIFT);
	host_info->num_cpus = mp_ncpus;

	rc = ena_com_set_host_attributes(ena_dev);
	if (unlikely(rc != 0)) {
		if (rc == EOPNOTSUPP)
			ena_trace(ENA_WARNING, "Cannot set host attributes\n");
		else
			ena_trace(ENA_ALERT, "Cannot set host attributes\n");

		goto err;
	}

	return;

err:
	ena_com_delete_host_info(ena_dev);
}