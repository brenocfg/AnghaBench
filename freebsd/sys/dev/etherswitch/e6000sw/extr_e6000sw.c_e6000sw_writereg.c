#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sw_addr; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ e6000sw_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  E6000SW_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_WRITE (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  MVSWITCH_MULTICHIP (TYPE_1__*) ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int SMI_CMD ; 
 int SMI_CMD_DEV_ADDR ; 
 int SMI_CMD_DEV_ADDR_MASK ; 
 int SMI_CMD_OP_C22_WRITE ; 
 int SMI_CMD_REG_ADDR_MASK ; 
 int SMI_DATA ; 
 scalar_t__ e6000sw_smi_waitready (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static __inline void
e6000sw_writereg(e6000sw_softc_t *sc, int addr, int reg, int val)
{

	E6000SW_LOCK_ASSERT(sc, SA_XLOCKED);

	if (!MVSWITCH_MULTICHIP(sc)) {
		MDIO_WRITE(sc->dev, addr, reg, val);
		return;
	}

	if (e6000sw_smi_waitready(sc, sc->sw_addr)) {
		printf("e6000sw: readreg timeout\n");
		return;
	}
	MDIO_WRITE(sc->dev, sc->sw_addr, SMI_DATA, val);
	MDIO_WRITE(sc->dev, sc->sw_addr, SMI_CMD,
	    SMI_CMD_OP_C22_WRITE | (reg & SMI_CMD_REG_ADDR_MASK) |
	    ((addr << SMI_CMD_DEV_ADDR) & SMI_CMD_DEV_ADDR_MASK));
}