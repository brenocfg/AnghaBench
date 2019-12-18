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
struct ipmi_user {int dummy; } ;
struct device {int dummy; } ;
struct acpi_ipmi_device {int ipmi_ifnum; struct ipmi_user* user_interface; int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; int /*<<< orphan*/  tx_msg_lock; int /*<<< orphan*/  tx_msg_list; int /*<<< orphan*/  head; int /*<<< orphan*/  kref; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  ipmi_hndlrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__ driver_data ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int ipmi_create_user (int,int /*<<< orphan*/ *,struct acpi_ipmi_device*,struct ipmi_user**) ; 
 int /*<<< orphan*/  kfree (struct acpi_ipmi_device*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct acpi_ipmi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct acpi_ipmi_device *
ipmi_dev_alloc(int iface, struct device *dev, acpi_handle handle)
{
	struct acpi_ipmi_device *ipmi_device;
	int err;
	struct ipmi_user *user;

	ipmi_device = kzalloc(sizeof(*ipmi_device), GFP_KERNEL);
	if (!ipmi_device)
		return NULL;

	kref_init(&ipmi_device->kref);
	INIT_LIST_HEAD(&ipmi_device->head);
	INIT_LIST_HEAD(&ipmi_device->tx_msg_list);
	spin_lock_init(&ipmi_device->tx_msg_lock);
	ipmi_device->handle = handle;
	ipmi_device->dev = get_device(dev);
	ipmi_device->ipmi_ifnum = iface;

	err = ipmi_create_user(iface, &driver_data.ipmi_hndlrs,
			       ipmi_device, &user);
	if (err) {
		put_device(dev);
		kfree(ipmi_device);
		return NULL;
	}
	ipmi_device->user_interface = user;

	return ipmi_device;
}