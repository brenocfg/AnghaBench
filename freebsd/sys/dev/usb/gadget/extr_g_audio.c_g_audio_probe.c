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
struct TYPE_2__ {scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; } ;
struct usb_attach_arg {scalar_t__ usb_mode; TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int ENXIO ; 
 scalar_t__ UICLASS_AUDIO ; 
 scalar_t__ UISUBCLASS_AUDIOCONTROL ; 
 scalar_t__ USB_MODE_DEVICE ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_audio_probe(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);

	DPRINTFN(11, "\n");

	if (uaa->usb_mode != USB_MODE_DEVICE)
		return (ENXIO);

	if ((uaa->info.bInterfaceClass == UICLASS_AUDIO) &&
	    (uaa->info.bInterfaceSubClass == UISUBCLASS_AUDIOCONTROL))
		return (0);

	return (ENXIO);
}