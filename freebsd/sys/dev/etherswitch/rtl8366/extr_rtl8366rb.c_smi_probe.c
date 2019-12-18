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
typedef  char uint16_t ;
struct rtl8366rb_softc {int /*<<< orphan*/  chip_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*,char) ; 
 int ENXIO ; 
 int /*<<< orphan*/  IICBUS_STOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIC_FASTEST ; 
 int /*<<< orphan*/  IIC_LAST_READ ; 
 int /*<<< orphan*/  IIC_WAIT ; 
 int /*<<< orphan*/  RTL8366RB ; 
 int RTL8366RB_CIR ; 
 char RTL8366RB_CIR_ID8366RB ; 
 int /*<<< orphan*/  RTL8366SR ; 
 int RTL8366SR_CIR ; 
 char RTL8366SR_CIR_ID8366SR ; 
 int RTL8366_IIC_ADDR ; 
 int RTL_IICBUS_READ ; 
 int /*<<< orphan*/  RTL_IICBUS_TIMEOUT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct rtl8366rb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int iicbus_read (int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int iicbus_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_stop (int /*<<< orphan*/ ) ; 
 int iicbus_write (int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smi_probe(device_t dev)
{
	struct rtl8366rb_softc *sc;
	device_t iicbus, iicha;
	int err, i, j;
	uint16_t chipid;
	char bytes[2];
	int xferd;

	sc = device_get_softc(dev);

	iicbus = device_get_parent(dev);
	iicha = device_get_parent(iicbus);

	for (i = 0; i < 2; ++i) {
		iicbus_reset(iicbus, IIC_FASTEST, RTL8366_IIC_ADDR, NULL);
		for (j=3; j--; ) {
			IICBUS_STOP(iicha);
			/*
			 * we go directly to the host adapter because iicbus.c
			 * only issues a stop on a bus that was successfully started.
			 */
		}
		err = iicbus_request_bus(iicbus, dev, IIC_WAIT);
		if (err != 0)
			goto out;
		err = iicbus_start(iicbus, RTL8366_IIC_ADDR | RTL_IICBUS_READ, RTL_IICBUS_TIMEOUT);
		if (err != 0)
			goto out;
		if (i == 0) {
			bytes[0] = RTL8366RB_CIR & 0xff;
			bytes[1] = (RTL8366RB_CIR >> 8) & 0xff;
		} else {
			bytes[0] = RTL8366SR_CIR & 0xff;
			bytes[1] = (RTL8366SR_CIR >> 8) & 0xff;
		}
		err = iicbus_write(iicbus, bytes, 2, &xferd, RTL_IICBUS_TIMEOUT);
		if (err != 0)
			goto out;
		err = iicbus_read(iicbus, bytes, 2, &xferd, IIC_LAST_READ, 0);
		if (err != 0)
			goto out;
		chipid = ((bytes[1] & 0xff) << 8) | (bytes[0] & 0xff);
		if (i == 0 && chipid == RTL8366RB_CIR_ID8366RB) {
			DPRINTF(dev, "chip id 0x%04x\n", chipid);
			sc->chip_type = RTL8366RB;
			err = 0;
			break;
		}
		if (i == 1 && chipid == RTL8366SR_CIR_ID8366SR) {
			DPRINTF(dev, "chip id 0x%04x\n", chipid);
			sc->chip_type = RTL8366SR;
			err = 0;
			break;
		}
		if (i == 0) {
			iicbus_stop(iicbus);
			iicbus_release_bus(iicbus, dev);
		}
	}
	if (i == 2)
		err = ENXIO;
out:
	iicbus_stop(iicbus);
	iicbus_release_bus(iicbus, dev);
	return (err == 0 ? 0 : ENXIO);
}