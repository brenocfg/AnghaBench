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
struct usb_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct usb_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_driver_list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_linux_driver_list ; 
 int /*<<< orphan*/  usb_needs_explore_all () ; 

void
usb_linux_register(void *arg)
{
	struct usb_driver *drv = arg;

	mtx_lock(&Giant);
	LIST_INSERT_HEAD(&usb_linux_driver_list, drv, linux_driver_list);
	mtx_unlock(&Giant);

	usb_needs_explore_all();
}