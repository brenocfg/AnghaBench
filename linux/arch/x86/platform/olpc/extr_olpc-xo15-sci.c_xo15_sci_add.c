#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {scalar_t__ valid; } ;
struct TYPE_7__ {TYPE_1__ flags; } ;
struct acpi_device {TYPE_4__ dev; TYPE_2__ wakeup; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_8__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_GPE_EDGE_TRIGGERED ; 
 int /*<<< orphan*/  EC_SCI_SRC_ALL ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  XO15_SCI_CLASS ; 
 int /*<<< orphan*/  XO15_SCI_DEVICE_NAME ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_enable_gpe (int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_install_gpe_handler (int /*<<< orphan*/ *,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_remove_gpe_handler (int /*<<< orphan*/ *,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,unsigned long long) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_4__*,int) ; 
 TYPE_3__ lid_wake_on_close_attr ; 
 int /*<<< orphan*/  olpc_ec_mask_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_sci_queue () ; 
 int /*<<< orphan*/  sci_work ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long long xo15_sci_gpe ; 
 int /*<<< orphan*/  xo15_sci_gpe_handler ; 

__attribute__((used)) static int xo15_sci_add(struct acpi_device *device)
{
	unsigned long long tmp;
	acpi_status status;
	int r;

	if (!device)
		return -EINVAL;

	strcpy(acpi_device_name(device), XO15_SCI_DEVICE_NAME);
	strcpy(acpi_device_class(device), XO15_SCI_CLASS);

	/* Get GPE bit assignment (EC events). */
	status = acpi_evaluate_integer(device->handle, "_GPE", NULL, &tmp);
	if (ACPI_FAILURE(status))
		return -EINVAL;

	xo15_sci_gpe = tmp;
	status = acpi_install_gpe_handler(NULL, xo15_sci_gpe,
					  ACPI_GPE_EDGE_TRIGGERED,
					  xo15_sci_gpe_handler, device);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	dev_info(&device->dev, "Initialized, GPE = 0x%lx\n", xo15_sci_gpe);

	r = sysfs_create_file(&device->dev.kobj, &lid_wake_on_close_attr.attr);
	if (r)
		goto err_sysfs;

	/* Flush queue, and enable all SCI events */
	process_sci_queue();
	olpc_ec_mask_write(EC_SCI_SRC_ALL);

	acpi_enable_gpe(NULL, xo15_sci_gpe);

	/* Enable wake-on-EC */
	if (device->wakeup.flags.valid)
		device_init_wakeup(&device->dev, true);

	return 0;

err_sysfs:
	acpi_remove_gpe_handler(NULL, xo15_sci_gpe, xo15_sci_gpe_handler);
	cancel_work_sync(&sci_work);
	return r;
}