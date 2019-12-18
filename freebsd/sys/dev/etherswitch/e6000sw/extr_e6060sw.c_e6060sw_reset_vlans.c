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
typedef  int uint32_t ;
struct e6060sw_softc {int numports; scalar_t__ vlan_mode; scalar_t__ smi_offset; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CORE_REGISTER ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  MDIO_WRITEREG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PORT_VLAN_MAP ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct e6060sw_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
e6060sw_reset_vlans(device_t dev)
{
	struct e6060sw_softc *sc;
	uint32_t ports;
	int i;
	int data;

	sc = device_get_softc(dev);

	for (i = 0; i <= sc->numports; i++) {
		ports = (1 << (sc->numports + 1)) - 1;
		ports &= ~(1 << i);
		if (sc->vlan_mode == ETHERSWITCH_VLAN_PORT) {
			data = i << 12;
		} else if (sc->vlan_mode == 0) {
			data = 1 << 8;
		} else {
			data = 0;
		}
		data |= ports;
		MDIO_WRITEREG(device_get_parent(dev),
		    CORE_REGISTER + sc->smi_offset + i, PORT_VLAN_MAP, data);
	}
}