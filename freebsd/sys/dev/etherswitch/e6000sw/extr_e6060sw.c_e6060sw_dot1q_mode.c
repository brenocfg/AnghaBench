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
struct e6060sw_softc {int numports; scalar_t__ smi_offset; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CORE_REGISTER ; 
 int DOT1QMODEMASK ; 
 int DOT1QMODESHIFT ; 
 int MDIO_READREG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_WRITEREG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PORT_CONTROL2 ; 
 int /*<<< orphan*/  PORT_DEFVLAN ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct e6060sw_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
e6060sw_dot1q_mode(device_t dev, int mode)
{
	struct e6060sw_softc *sc;
	int i;
	int data;

	sc = device_get_softc(dev);

	for (i = 0; i <= sc->numports; i++) {
		data = MDIO_READREG(device_get_parent(dev),
		    CORE_REGISTER + sc->smi_offset + i, PORT_CONTROL2);
		data &= ~(DOT1QMODEMASK << DOT1QMODESHIFT);
		data |= mode << DOT1QMODESHIFT;
		MDIO_WRITEREG(device_get_parent(dev),
		    CORE_REGISTER + sc->smi_offset + i, PORT_CONTROL2, data);

		data = MDIO_READREG(device_get_parent(dev), 
		    CORE_REGISTER + sc->smi_offset + i,
		    PORT_DEFVLAN);
		data &= ~0xfff;
		data |= 1;
		MDIO_WRITEREG(device_get_parent(dev), 
		    CORE_REGISTER + sc->smi_offset + i,
		    PORT_DEFVLAN, data);
	}
}