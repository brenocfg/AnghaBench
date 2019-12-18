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
struct device {int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/ * type; } ;
struct ata_port {int /*<<< orphan*/  host; int /*<<< orphan*/  link; int /*<<< orphan*/  print_id; struct device tdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_acpi_bind_port (struct ata_port*) ; 
 int /*<<< orphan*/  ata_host_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_port_type ; 
 int ata_tlink_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ata_tport_release ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  device_enable_async_suspend (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  transport_add_device (struct device*) ; 
 int /*<<< orphan*/  transport_configure_device (struct device*) ; 
 int /*<<< orphan*/  transport_destroy_device (struct device*) ; 
 int /*<<< orphan*/  transport_remove_device (struct device*) ; 
 int /*<<< orphan*/  transport_setup_device (struct device*) ; 

int ata_tport_add(struct device *parent,
		  struct ata_port *ap)
{
	int error;
	struct device *dev = &ap->tdev;

	device_initialize(dev);
	dev->type = &ata_port_type;

	dev->parent = parent;
	ata_host_get(ap->host);
	dev->release = ata_tport_release;
	dev_set_name(dev, "ata%d", ap->print_id);
	transport_setup_device(dev);
	ata_acpi_bind_port(ap);
	error = device_add(dev);
	if (error) {
		goto tport_err;
	}

	device_enable_async_suspend(dev);
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	pm_runtime_forbid(dev);

	transport_add_device(dev);
	transport_configure_device(dev);

	error = ata_tlink_add(&ap->link);
	if (error) {
		goto tport_link_err;
	}
	return 0;

 tport_link_err:
	transport_remove_device(dev);
	device_del(dev);

 tport_err:
	transport_destroy_device(dev);
	put_device(dev);
	ata_host_put(ap->host);
	return error;
}