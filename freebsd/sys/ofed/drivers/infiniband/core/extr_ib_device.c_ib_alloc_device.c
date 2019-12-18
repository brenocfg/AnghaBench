#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * class; int /*<<< orphan*/ * parent; } ;
struct ib_device {int /*<<< orphan*/  port_list; int /*<<< orphan*/  client_data_list; int /*<<< orphan*/  client_data_lock; int /*<<< orphan*/  event_handler_lock; int /*<<< orphan*/  event_handler_list; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct ib_device*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  ib_class ; 
 struct ib_device* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_root_device ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ib_device *ib_alloc_device(size_t size)
{
	struct ib_device *device;

	if (WARN_ON(size < sizeof(struct ib_device)))
		return NULL;

	device = kzalloc(size, GFP_KERNEL);
	if (!device)
		return NULL;

	device->dev.parent = &linux_root_device;
	device->dev.class = &ib_class;
	device_initialize(&device->dev);

	dev_set_drvdata(&device->dev, device);

	INIT_LIST_HEAD(&device->event_handler_list);
	spin_lock_init(&device->event_handler_lock);
	spin_lock_init(&device->client_data_lock);
	INIT_LIST_HEAD(&device->client_data_list);
	INIT_LIST_HEAD(&device->port_list);

	return device;
}