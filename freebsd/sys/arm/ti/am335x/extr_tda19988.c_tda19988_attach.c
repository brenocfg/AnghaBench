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
struct tda19988_softc {int sc_cec_addr; int /*<<< orphan*/  sc_edid_len; int /*<<< orphan*/  sc_edid; int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDID_LENGTH ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 struct tda19988_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda19988_start (struct tda19988_softc*) ; 

__attribute__((used)) static int
tda19988_attach(device_t dev)
{
	struct tda19988_softc *sc;
	phandle_t node;

	sc = device_get_softc(dev);

	sc->sc_dev = dev;
	sc->sc_addr = iicbus_get_addr(dev);
	sc->sc_cec_addr = (0x34 << 1); /* hardcoded */
	sc->sc_edid = malloc(EDID_LENGTH, M_DEVBUF, M_WAITOK | M_ZERO);
	sc->sc_edid_len = EDID_LENGTH;

	device_set_desc(dev, "NXP TDA19988 HDMI transmitter");

	node = ofw_bus_get_node(dev);
	OF_device_register_xref(OF_xref_from_node(node), dev);

	tda19988_start(sc);

	return (0);
}