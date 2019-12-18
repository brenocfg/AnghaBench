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
struct acpi_ec {scalar_t__ command_addr; scalar_t__ data_addr; int /*<<< orphan*/  handle; } ;
struct acpi_device {struct acpi_ec* driver_data; int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ECDT_HID ; 
 int /*<<< orphan*/  ACPI_EC_CLASS ; 
 int /*<<< orphan*/  ACPI_EC_DEVICE_NAME ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_hid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 struct acpi_ec* acpi_ec_alloc () ; 
 int /*<<< orphan*/  acpi_ec_free (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_remove_query_handlers (struct acpi_ec*,int,int /*<<< orphan*/ ) ; 
 int acpi_ec_setup (struct acpi_ec*,int) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_handle_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  acpi_walk_dep_device_list (int /*<<< orphan*/ ) ; 
 struct acpi_ec* boot_ec ; 
 int boot_ec_is_ecdt ; 
 scalar_t__ ec_parse_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_ec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_ec_add(struct acpi_device *device)
{
	struct acpi_ec *ec = NULL;
	bool dep_update = true;
	acpi_status status;
	int ret;

	strcpy(acpi_device_name(device), ACPI_EC_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_EC_CLASS);

	if (!strcmp(acpi_device_hid(device), ACPI_ECDT_HID)) {
		boot_ec_is_ecdt = true;
		ec = boot_ec;
		dep_update = false;
	} else {
		ec = acpi_ec_alloc();
		if (!ec)
			return -ENOMEM;

		status = ec_parse_device(device->handle, 0, ec, NULL);
		if (status != AE_CTRL_TERMINATE) {
			ret = -EINVAL;
			goto err_alloc;
		}

		if (boot_ec && ec->command_addr == boot_ec->command_addr &&
		    ec->data_addr == boot_ec->data_addr) {
			boot_ec_is_ecdt = false;
			/*
			 * Trust PNP0C09 namespace location rather than
			 * ECDT ID. But trust ECDT GPE rather than _GPE
			 * because of ASUS quirks, so do not change
			 * boot_ec->gpe to ec->gpe.
			 */
			boot_ec->handle = ec->handle;
			acpi_handle_debug(ec->handle, "duplicated.\n");
			acpi_ec_free(ec);
			ec = boot_ec;
		}
	}

	ret = acpi_ec_setup(ec, true);
	if (ret)
		goto err_query;

	if (ec == boot_ec)
		acpi_handle_info(boot_ec->handle,
				 "Boot %s EC used to handle transactions and events\n",
				 boot_ec_is_ecdt ? "ECDT" : "DSDT");

	device->driver_data = ec;

	ret = !!request_region(ec->data_addr, 1, "EC data");
	WARN(!ret, "Could not request EC data io port 0x%lx", ec->data_addr);
	ret = !!request_region(ec->command_addr, 1, "EC cmd");
	WARN(!ret, "Could not request EC cmd io port 0x%lx", ec->command_addr);

	if (dep_update) {
		/* Reprobe devices depending on the EC */
		acpi_walk_dep_device_list(ec->handle);
	}
	acpi_handle_debug(ec->handle, "enumerated.\n");
	return 0;

err_query:
	if (ec != boot_ec)
		acpi_ec_remove_query_handlers(ec, true, 0);
err_alloc:
	if (ec != boot_ec)
		acpi_ec_free(ec);
	return ret;
}