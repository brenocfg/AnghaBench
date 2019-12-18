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
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; struct drvdb_ent* driver_ivar; } ;
struct ndisusb_softc {int dummy; } ;
struct ndis_usb_type {scalar_t__ ndis_vid; scalar_t__ ndis_did; int /*<<< orphan*/ * ndis_name; } ;
struct ndis_softc {int ndis_devidx; int /*<<< orphan*/  ndisusb_dev; int /*<<< orphan*/  ndis_iftype; int /*<<< orphan*/  ndis_regvals; int /*<<< orphan*/  ndis_dobj; int /*<<< orphan*/  ndisusb_mtx; int /*<<< orphan*/  ndis_dev; } ;
struct drvdb_ent {struct ndis_usb_type* windrv_devlist; int /*<<< orphan*/  windrv_regvals; int /*<<< orphan*/  windrv_object; } ;
typedef  int /*<<< orphan*/  driver_object ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  PNPBus ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct ndisusb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ndis_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windrv_create_pdo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * windrv_lookup (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ndisusb_attach(device_t self)
{
	const struct drvdb_ent	*db;
	struct ndisusb_softc *dummy = device_get_softc(self);
	struct usb_attach_arg *uaa = device_get_ivars(self);
	struct ndis_softc	*sc;
	struct ndis_usb_type	*t;
	driver_object		*drv;
	int			devidx = 0;

	device_set_usb_desc(self);
	db = uaa->driver_ivar;
	sc = (struct ndis_softc *)dummy;
	sc->ndis_dev = self;
	mtx_init(&sc->ndisusb_mtx, "NDIS USB", MTX_NETWORK_LOCK, MTX_DEF);
	sc->ndis_dobj = db->windrv_object;
	sc->ndis_regvals = db->windrv_regvals;
	sc->ndis_iftype = PNPBus;
	sc->ndisusb_dev = uaa->device;

	/* Create PDO for this device instance */

	drv = windrv_lookup(0, "USB Bus");
	windrv_create_pdo(drv, self);

	/* Figure out exactly which device we matched. */

	t = db->windrv_devlist;

	while (t->ndis_name != NULL) {
		if ((uaa->info.idVendor == t->ndis_vid) &&
		    (uaa->info.idProduct == t->ndis_did)) {
			sc->ndis_devidx = devidx;
			break;
		}
		t++;
		devidx++;
	}

	if (ndis_attach(self) != 0)
		return (ENXIO);

	return (0);
}