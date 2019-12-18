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
struct TYPE_2__ {scalar_t__ bConfigIndex; scalar_t__ bIfaceIndex; } ;
struct usb_attach_arg {scalar_t__ usb_mode; struct drvdb_ent* driver_ivar; TYPE_1__ info; } ;
struct drvdb_ent {int dummy; } ;
typedef  int /*<<< orphan*/  matchfuncptr ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ NDISUSB_CONFIG_NO ; 
 scalar_t__ NDISUSB_IFACE_INDEX ; 
 scalar_t__ USB_MODE_HOST ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ ndisusb_devcompare ; 
 int /*<<< orphan*/ * windrv_lookup (int /*<<< orphan*/ ,char*) ; 
 struct drvdb_ent* windrv_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ndisusb_match(device_t self)
{
	struct drvdb_ent *db;
	struct usb_attach_arg *uaa = device_get_ivars(self);

	if (uaa->usb_mode != USB_MODE_HOST)
		return (ENXIO);
	if (uaa->info.bConfigIndex != NDISUSB_CONFIG_NO)
		return (ENXIO);
	if (uaa->info.bIfaceIndex != NDISUSB_IFACE_INDEX)
		return (ENXIO);

	if (windrv_lookup(0, "USB Bus") == NULL)
		return (ENXIO);

	db = windrv_match((matchfuncptr)ndisusb_devcompare, self);
	if (db == NULL)
		return (ENXIO);
	uaa->driver_ivar = db;

	return (0);
}