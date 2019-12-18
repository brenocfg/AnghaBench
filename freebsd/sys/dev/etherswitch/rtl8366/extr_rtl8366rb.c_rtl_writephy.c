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
struct rtl8366rb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INCRVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVERR (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*,int) ; 
 int EBUSY ; 
 int EIO ; 
 int ENXIO ; 
 int RTL8366_NUM_PHYS ; 
 int RTL8366_NUM_PHY_REG ; 
 int /*<<< orphan*/  RTL8366_PACR ; 
 int RTL8366_PACR_WRITE ; 
 int /*<<< orphan*/  RTL8366_PHYREG (int,int /*<<< orphan*/ ,int) ; 
 int RTL_IICBUS_RETRIES ; 
 int /*<<< orphan*/  RTL_IICBUS_RETRY_SLEEP ; 
 int RTL_WAITOK ; 
 struct rtl8366rb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_access_retries ; 
 int smi_acquire (struct rtl8366rb_softc*,int) ; 
 int /*<<< orphan*/  smi_release (struct rtl8366rb_softc*,int) ; 
 int smi_write_locked (struct rtl8366rb_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
rtl_writephy(device_t dev, int phy, int reg, int data)
{
	struct rtl8366rb_softc *sc;
	int err, i, sleep;
	
	sc = device_get_softc(dev);

	if (phy < 0 || phy >= RTL8366_NUM_PHYS)
		return (ENXIO);
	if (reg < 0 || reg >= RTL8366_NUM_PHY_REG)
		return (ENXIO);
	sleep = RTL_WAITOK;
	err = smi_acquire(sc, sleep);
	if (err != 0)
		return (EBUSY);
	for (i = RTL_IICBUS_RETRIES; i--; ) {
		err = smi_write_locked(sc, RTL8366_PACR, RTL8366_PACR_WRITE, sleep);
		if (err == 0)
			err = smi_write_locked(sc, RTL8366_PHYREG(phy, 0, reg), data, sleep);
		if (err == 0) {
			break;
		}
		DEBUG_INCRVAR(phy_access_retries);
		DPRINTF(dev, "rtl_writephy(): chip not responsive, retrying %d more tiems\n", i);
		pause("rtl_writephy", RTL_IICBUS_RETRY_SLEEP);
	}
	smi_release(sc, sleep);
	DEVERR(dev, err, "rtl_writephy()=%d: phy=%d.%02x\n", phy, reg);
	return (err == 0 ? 0 : EIO);
}