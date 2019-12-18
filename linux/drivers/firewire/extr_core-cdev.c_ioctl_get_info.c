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
struct fw_cdev_get_info {scalar_t__ rom; size_t rom_length; scalar_t__ bus_reset; int /*<<< orphan*/  bus_reset_closure; int /*<<< orphan*/  card; int /*<<< orphan*/  version; } ;
union ioctl_arg {struct fw_cdev_get_info get_info; } ;
struct fw_cdev_event_bus_reset {int dummy; } ;
struct client {TYPE_2__* device; int /*<<< orphan*/  link; int /*<<< orphan*/  bus_reset_closure; int /*<<< orphan*/  version; } ;
struct TYPE_4__ {int config_rom_length; int /*<<< orphan*/  client_list_mutex; int /*<<< orphan*/  client_list; struct fw_cdev_event_bus_reset* config_rom; TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  FW_CDEV_KERNEL_VERSION ; 
 unsigned long copy_to_user (int /*<<< orphan*/ ,struct fw_cdev_event_bus_reset*,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_bus_reset_event (struct fw_cdev_event_bus_reset*,struct client*) ; 
 int /*<<< orphan*/  fw_device_rwsem ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int min (size_t,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_to_uptr (scalar_t__) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioctl_get_info(struct client *client, union ioctl_arg *arg)
{
	struct fw_cdev_get_info *a = &arg->get_info;
	struct fw_cdev_event_bus_reset bus_reset;
	unsigned long ret = 0;

	client->version = a->version;
	a->version = FW_CDEV_KERNEL_VERSION;
	a->card = client->device->card->index;

	down_read(&fw_device_rwsem);

	if (a->rom != 0) {
		size_t want = a->rom_length;
		size_t have = client->device->config_rom_length * 4;

		ret = copy_to_user(u64_to_uptr(a->rom),
				   client->device->config_rom, min(want, have));
	}
	a->rom_length = client->device->config_rom_length * 4;

	up_read(&fw_device_rwsem);

	if (ret != 0)
		return -EFAULT;

	mutex_lock(&client->device->client_list_mutex);

	client->bus_reset_closure = a->bus_reset_closure;
	if (a->bus_reset != 0) {
		fill_bus_reset_event(&bus_reset, client);
		/* unaligned size of bus_reset is 36 bytes */
		ret = copy_to_user(u64_to_uptr(a->bus_reset), &bus_reset, 36);
	}
	if (ret == 0 && list_empty(&client->link))
		list_add_tail(&client->link, &client->device->client_list);

	mutex_unlock(&client->device->client_list_mutex);

	return ret ? -EFAULT : 0;
}