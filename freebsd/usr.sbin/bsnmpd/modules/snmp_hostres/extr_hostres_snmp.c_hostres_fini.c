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

/* Variables and functions */
 int /*<<< orphan*/  HRDBG (char*) ; 
 int /*<<< orphan*/  fini_device_tbl () ; 
 int /*<<< orphan*/  fini_disk_storage_tbl () ; 
 int /*<<< orphan*/  fini_fs_tbl () ; 
 int /*<<< orphan*/  fini_network_tbl () ; 
 int /*<<< orphan*/  fini_partition_tbl () ; 
 int /*<<< orphan*/  fini_printer_tbl () ; 
 int /*<<< orphan*/  fini_processor_tbl () ; 
 int /*<<< orphan*/  fini_scalars () ; 
 int /*<<< orphan*/  fini_storage_tbl () ; 
 int /*<<< orphan*/  fini_swins_tbl () ; 
 int /*<<< orphan*/  fini_swrun_tbl () ; 
 scalar_t__ host_registration_id ; 
 int /*<<< orphan*/ * hr_kd ; 
 int /*<<< orphan*/  kvm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  or_unregister (scalar_t__) ; 

__attribute__((used)) static int
hostres_fini(void)
{

	if (hr_kd != NULL)
		(void)kvm_close(hr_kd);

	fini_storage_tbl();
	fini_fs_tbl();
	fini_processor_tbl();
	fini_disk_storage_tbl();
	fini_device_tbl();
	fini_partition_tbl();
	fini_network_tbl();
	fini_printer_tbl();

	fini_swrun_tbl();
	fini_swins_tbl();

	fini_scalars();

	if (host_registration_id > 0)
		or_unregister(host_registration_id);

	HRDBG("done.");
	return (0);
}