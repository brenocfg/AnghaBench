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
struct TYPE_2__ {scalar_t__ idVendor; scalar_t__ idProduct; } ;
struct usb_attach_arg {TYPE_1__ info; } ;
struct ndis_usb_type {scalar_t__ ndis_vid; scalar_t__ ndis_did; int /*<<< orphan*/ * ndis_name; } ;
typedef  scalar_t__ interface_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ PNPBus ; 
 int TRUE ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ndisusb_devcompare(interface_type bustype, struct ndis_usb_type *t, device_t dev)
{
	struct usb_attach_arg *uaa;

	if (bustype != PNPBus)
		return (FALSE);

	uaa = device_get_ivars(dev);

	while (t->ndis_name != NULL) {
		if ((uaa->info.idVendor == t->ndis_vid) &&
		    (uaa->info.idProduct == t->ndis_did)) {
			device_set_desc(dev, t->ndis_name);
			return (TRUE);
		}
		t++;
	}

	return (FALSE);
}