#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int libusb_hotplug_event ;
typedef  TYPE_1__* libusb_hotplug_callback_handle ;
struct TYPE_8__ {int /*<<< orphan*/  os_priv; } ;
typedef  TYPE_2__ libusb_device ;
typedef  int /*<<< orphan*/  libusb_context ;
struct TYPE_9__ {scalar_t__ idVendor; scalar_t__ idProduct; scalar_t__ bDeviceClass; } ;
struct TYPE_7__ {int events; scalar_t__ vendor; scalar_t__ product; scalar_t__ devclass; int (* fn ) (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  user_data; } ;

/* Variables and functions */
 scalar_t__ LIBUSB_HOTPLUG_MATCH_ANY ; 
 TYPE_6__* libusb20_dev_get_device_desc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
libusb_hotplug_filter(libusb_context *ctx, libusb_hotplug_callback_handle pcbh,
    libusb_device *dev, libusb_hotplug_event event)
{
	if (!(pcbh->events & event))
		return (0);
	if (pcbh->vendor != LIBUSB_HOTPLUG_MATCH_ANY &&
	    pcbh->vendor != libusb20_dev_get_device_desc(dev->os_priv)->idVendor)
		return (0);
	if (pcbh->product != LIBUSB_HOTPLUG_MATCH_ANY &&
	    pcbh->product != libusb20_dev_get_device_desc(dev->os_priv)->idProduct)
		return (0);
	if (pcbh->devclass != LIBUSB_HOTPLUG_MATCH_ANY &&
	    pcbh->devclass != libusb20_dev_get_device_desc(dev->os_priv)->bDeviceClass)
		return (0);
	return (pcbh->fn(ctx, dev, event, pcbh->user_data));
}