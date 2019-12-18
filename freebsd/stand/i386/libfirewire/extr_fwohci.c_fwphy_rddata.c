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
typedef  int uint32_t ;
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct fwohci_softc {TYPE_1__ fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FWOHCI_INTSTAT ; 
 int /*<<< orphan*/  FWOHCI_INTSTATCLR ; 
 int MAX_RETRY ; 
 int OHCI_INT_REG_FAIL ; 
 int /*<<< orphan*/  OHCI_PHYACCESS ; 
 int OREAD (struct fwohci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int) ; 
 int PHYDEV_RDCMD ; 
 int PHYDEV_RDDATA ; 
 int PHYDEV_RDDONE ; 
 int PHYDEV_REGADDR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ firewire_debug ; 

__attribute__((used)) static uint32_t
fwphy_rddata(struct fwohci_softc *sc,  u_int addr)
{
	uint32_t fun, stat;
	u_int i, retry = 0;

	addr &= 0xf;
#define MAX_RETRY 100
again:
	OWRITE(sc, FWOHCI_INTSTATCLR, OHCI_INT_REG_FAIL);
	fun = PHYDEV_RDCMD | (addr << PHYDEV_REGADDR);
	OWRITE(sc, OHCI_PHYACCESS, fun);
	for ( i = 0 ; i < MAX_RETRY ; i ++ ){
		fun = OREAD(sc, OHCI_PHYACCESS);
		if ((fun & PHYDEV_RDCMD) == 0 && (fun & PHYDEV_RDDONE) != 0)
			break;
		DELAY(100);
	}
	if(i >= MAX_RETRY) {
		if (firewire_debug)
			device_printf(sc->fc.dev, "phy read failed(1).\n");
		if (++retry < MAX_RETRY) {
			DELAY(100);
			goto again;
		}
	}
	/* Make sure that SCLK is started */
	stat = OREAD(sc, FWOHCI_INTSTAT);
	if ((stat & OHCI_INT_REG_FAIL) != 0 ||
			((fun >> PHYDEV_REGADDR) & 0xf) != addr) {
		if (firewire_debug)
			device_printf(sc->fc.dev, "phy read failed(2).\n");
		if (++retry < MAX_RETRY) {
			DELAY(100);
			goto again;
		}
	}
	if (firewire_debug || retry >= MAX_RETRY)
		device_printf(sc->fc.dev, 
		    "fwphy_rddata: 0x%x loop=%d, retry=%d\n", addr, i, retry);
#undef MAX_RETRY
	return((fun >> PHYDEV_RDDATA )& 0xff);
}