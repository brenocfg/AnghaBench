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
typedef  int uint16_t ;
struct rtl8366rb_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTL_IICBUS_TIMEOUT ; 
 int /*<<< orphan*/  RTL_IICBUS_WRITE ; 
 int /*<<< orphan*/  RTL_SMI_ACQUIRED_ASSERT (struct rtl8366rb_softc*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_stop (int /*<<< orphan*/ ) ; 
 int iicbus_write (int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ) ; 
 int smi_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
smi_write_locked(struct rtl8366rb_softc *sc, uint16_t addr, uint16_t data, int sleep)
{
	int err;
	device_t iicbus;
	char bytes[4];
	int xferd;

	iicbus = device_get_parent(sc->dev);

	RTL_SMI_ACQUIRED_ASSERT(sc);
	bytes[0] = addr & 0xff;
	bytes[1] = (addr >> 8) & 0xff;
	bytes[2] = data & 0xff;
	bytes[3] = (data >> 8) & 0xff;

	err = smi_select(sc->dev, RTL_IICBUS_WRITE, sleep);
	if (err == 0)
		err = iicbus_write(iicbus, bytes, 4, &xferd, RTL_IICBUS_TIMEOUT);
	iicbus_stop(iicbus);

	return (err);
}