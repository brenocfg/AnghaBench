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
struct rtl8366rb_softc {scalar_t__ chip_type; } ;
struct iicbus_ivar {int addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INCRVAR (int /*<<< orphan*/ ) ; 
 struct iicbus_ivar* IICBUS_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IICBUS_STOP (int /*<<< orphan*/ ) ; 
 int IIC_ENOACK ; 
 scalar_t__ RTL8366SR ; 
 int RTL_IICBUS_RETRIES ; 
 int /*<<< orphan*/  RTL_IICBUS_RETRY_SLEEP ; 
 int /*<<< orphan*/  RTL_IICBUS_TIMEOUT ; 
 int /*<<< orphan*/  RTL_SMI_ACQUIRED_ASSERT (struct rtl8366rb_softc*) ; 
 int RTL_WAITOK ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct rtl8366rb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iic_select_retries ; 
 int iicbus_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smi_select(device_t dev, int op, int sleep)
{
	struct rtl8366rb_softc *sc;
	int err, i;
	device_t iicbus;
	struct iicbus_ivar *devi;
	int slave;

	sc = device_get_softc(dev);

	iicbus = device_get_parent(dev);
	devi = IICBUS_IVAR(dev);
	slave = devi->addr;

	RTL_SMI_ACQUIRED_ASSERT((struct rtl8366rb_softc *)device_get_softc(dev));

	if (sc->chip_type == RTL8366SR) {   // RTL8366SR work around
		// this is same work around at probe
		for (int i=3; i--; )
			IICBUS_STOP(device_get_parent(device_get_parent(dev)));
	}
	/*
	 * The chip does not use clock stretching when it is busy,
	 * instead ignoring the command. Retry a few times.
	 */
	for (i = RTL_IICBUS_RETRIES; i--; ) {
		err = iicbus_start(iicbus, slave | op, RTL_IICBUS_TIMEOUT);
		if (err != IIC_ENOACK)
			break;
		if (sleep == RTL_WAITOK) {
			DEBUG_INCRVAR(iic_select_retries);
			pause("smi_select", RTL_IICBUS_RETRY_SLEEP);
		} else
			break;
	}
	return (err);
}