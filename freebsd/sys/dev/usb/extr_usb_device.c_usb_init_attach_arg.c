#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_4__ {int /*<<< orphan*/  usb_mode; } ;
struct usb_device {int /*<<< orphan*/  curr_config_no; int /*<<< orphan*/  curr_config_index; TYPE_2__ ddesc; int /*<<< orphan*/  port_no; TYPE_1__ flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  bConfigNum; int /*<<< orphan*/  bConfigIndex; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; void* bcdDevice; void* idProduct; void* idVendor; } ;
struct usb_attach_arg {TYPE_3__ info; int /*<<< orphan*/  dev_state; int /*<<< orphan*/  port; int /*<<< orphan*/  usb_mode; struct usb_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAA_DEV_READY ; 
 void* UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct usb_attach_arg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
usb_init_attach_arg(struct usb_device *udev,
    struct usb_attach_arg *uaa)
{
	memset(uaa, 0, sizeof(*uaa));

	uaa->device = udev;
	uaa->usb_mode = udev->flags.usb_mode;
	uaa->port = udev->port_no;
	uaa->dev_state = UAA_DEV_READY;

	uaa->info.idVendor = UGETW(udev->ddesc.idVendor);
	uaa->info.idProduct = UGETW(udev->ddesc.idProduct);
	uaa->info.bcdDevice = UGETW(udev->ddesc.bcdDevice);
	uaa->info.bDeviceClass = udev->ddesc.bDeviceClass;
	uaa->info.bDeviceSubClass = udev->ddesc.bDeviceSubClass;
	uaa->info.bDeviceProtocol = udev->ddesc.bDeviceProtocol;
	uaa->info.bConfigIndex = udev->curr_config_index;
	uaa->info.bConfigNum = udev->curr_config_no;
}