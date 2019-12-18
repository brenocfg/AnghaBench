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
struct libusb_device_head {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  libusb_device ;
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct libusb_device_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hotplug_entry ; 
 int /*<<< orphan*/  libusb_free_device_list (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb_get_device_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ***) ; 

__attribute__((used)) static int
libusb_hotplug_enumerate(libusb_context *ctx, struct libusb_device_head *phead)
{
	libusb_device **ppdev;
	ssize_t count;
	ssize_t x;

	count = libusb_get_device_list(ctx, &ppdev);
	if (count < 0)
		return (-1);

	for (x = 0; x != count; x++)
		TAILQ_INSERT_TAIL(phead, ppdev[x], hotplug_entry);

	libusb_free_device_list(ppdev, 0);
	return (0);
}