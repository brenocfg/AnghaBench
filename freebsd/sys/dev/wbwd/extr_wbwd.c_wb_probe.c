#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct wb_softc {int /*<<< orphan*/  chip; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int device_id; char* descr; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int BUS_PROBE_SPECIFIC ; 
 int ENXIO ; 
 scalar_t__ SUPERIO_DEV_WDT ; 
 scalar_t__ SUPERIO_VENDOR_NUVOTON ; 
 scalar_t__ bootverbose ; 
 struct wb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int) ; 
 int superio_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ superio_get_type (int /*<<< orphan*/ ) ; 
 int superio_revid (int /*<<< orphan*/ ) ; 
 scalar_t__ superio_vendor (int /*<<< orphan*/ ) ; 
 TYPE_1__* wb_devs ; 

__attribute__((used)) static int
wb_probe(device_t dev)
{
	char buf[128];
	struct wb_softc *sc;
	int j;
	uint8_t devid;
	uint8_t revid;

	if (superio_vendor(dev) != SUPERIO_VENDOR_NUVOTON)
		return (ENXIO);
	if (superio_get_type(dev) != SUPERIO_DEV_WDT)
		return (ENXIO);

	sc = device_get_softc(dev);
	devid = superio_devid(dev) >> 8;
	revid = superio_revid(dev);
	for (j = 0; j < nitems(wb_devs); j++) {
		if (wb_devs[j].device_id == devid) {
			sc->chip = wb_devs[j].chip;
			snprintf(buf, sizeof(buf),
			    "%s (0x%02x/0x%02x) Watchdog Timer",
			    wb_devs[j].descr, devid, revid);
			device_set_desc_copy(dev, buf);
			return (BUS_PROBE_SPECIFIC);
		}
	}
	if (bootverbose) {
		device_printf(dev,
		    "unrecognized chip: devid 0x%02x, revid 0x%02x\n",
		    devid, revid);
	}
	return (ENXIO);
}