#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next_device; int /*<<< orphan*/  port; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  hdlcdev_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mgslpc_device_count ; 
 TYPE_1__* mgslpc_device_list ; 
 int /*<<< orphan*/  release_resources (TYPE_1__*) ; 
 int /*<<< orphan*/  serial_driver ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mgslpc_remove_device(MGSLPC_INFO *remove_info)
{
	MGSLPC_INFO *info = mgslpc_device_list;
	MGSLPC_INFO *last = NULL;

	while(info) {
		if (info == remove_info) {
			if (last)
				last->next_device = info->next_device;
			else
				mgslpc_device_list = info->next_device;
			tty_unregister_device(serial_driver, info->line);
#if SYNCLINK_GENERIC_HDLC
			hdlcdev_exit(info);
#endif
			release_resources(info);
			tty_port_destroy(&info->port);
			kfree(info);
			mgslpc_device_count--;
			return;
		}
		last = info;
		info = info->next_device;
	}
}