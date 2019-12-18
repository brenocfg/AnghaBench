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
struct e6060sw_softc {int sw_model; int smi_offset; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 scalar_t__ CORE_REGISTER ; 
 int E6060 ; 
 int E6063 ; 
 int E6065 ; 
 int ENXIO ; 
 int MDIO_READREG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_ID ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bzero (struct e6060sw_softc*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct e6060sw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 

__attribute__((used)) static int
e6060sw_probe(device_t dev)
{
	int data;
	struct e6060sw_softc *sc;
	int devid, i;
	char *devname;
	char desc[80];

	sc = device_get_softc(dev);
	bzero(sc, sizeof(*sc));

	devid = 0;
	for (i = 0; i < 2; ++i) {
		data = MDIO_READREG(device_get_parent(dev), 
		    CORE_REGISTER + i * 0x10, SWITCH_ID);
		if (bootverbose)
			device_printf(dev,"Switch Identifier Register %x\n",
			    data);

		devid = data >> 4;
		if (devid == E6060 || 
		    devid == E6063 || devid == E6065) {
			sc->sw_model = devid;
			sc->smi_offset = i * 0x10;
			break;
		}
	}

	if (devid == E6060)
		devname = "88E6060";
	else if (devid == E6063)
		devname = "88E6063";
	else if (devid == E6065)
		devname = "88E6065";
	else
		return (ENXIO);

	sprintf(desc, "Marvell %s MDIO switch driver at 0x%02x",
	    devname, sc->smi_offset);
	device_set_desc_copy(dev, desc);

	return (BUS_PROBE_DEFAULT);
}