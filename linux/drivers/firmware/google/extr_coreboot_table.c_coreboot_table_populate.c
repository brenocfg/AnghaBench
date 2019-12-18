#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct coreboot_table_header {int header_bytes; int table_entries; } ;
struct coreboot_table_entry {scalar_t__ size; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; struct device* parent; } ;
struct coreboot_device {TYPE_1__ dev; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  coreboot_bus_type ; 
 int /*<<< orphan*/  coreboot_device_release ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_register (TYPE_1__*) ; 
 struct coreboot_device* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static int coreboot_table_populate(struct device *dev, void *ptr)
{
	int i, ret;
	void *ptr_entry;
	struct coreboot_device *device;
	struct coreboot_table_entry *entry;
	struct coreboot_table_header *header = ptr;

	ptr_entry = ptr + header->header_bytes;
	for (i = 0; i < header->table_entries; i++) {
		entry = ptr_entry;

		device = kzalloc(sizeof(struct device) + entry->size, GFP_KERNEL);
		if (!device)
			return -ENOMEM;

		dev_set_name(&device->dev, "coreboot%d", i);
		device->dev.parent = dev;
		device->dev.bus = &coreboot_bus_type;
		device->dev.release = coreboot_device_release;
		memcpy(&device->entry, ptr_entry, entry->size);

		ret = device_register(&device->dev);
		if (ret) {
			put_device(&device->dev);
			return ret;
		}

		ptr_entry += entry->size;
	}

	return 0;
}