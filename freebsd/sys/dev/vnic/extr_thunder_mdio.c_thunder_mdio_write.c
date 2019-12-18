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
typedef  int uint64_t ;
struct thunder_mdio_softc {scalar_t__ mode; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 scalar_t__ MODE_IEEE_C22 ; 
 int /*<<< orphan*/  SMI_CMD ; 
 int SMI_CMD_PHY_ADR_MASK ; 
 int SMI_CMD_PHY_ADR_SHIFT ; 
 int SMI_CMD_PHY_OP_C22_WRITE ; 
 int SMI_CMD_PHY_OP_C45_WRITE ; 
 int SMI_CMD_PHY_REG_ADR_MASK ; 
 int SMI_CMD_PHY_REG_ADR_SHIFT ; 
 int /*<<< orphan*/  SMI_WR_DAT ; 
 int SMI_WR_DAT_DAT_MASK ; 
 int SMI_WR_DAT_PENDING ; 
 struct thunder_mdio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mdio_reg_read (struct thunder_mdio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_reg_write (struct thunder_mdio_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thunder_mdio_set_mode (struct thunder_mdio_softc*,scalar_t__) ; 

__attribute__((used)) static int
thunder_mdio_write(device_t dev, int phy, int reg, int data)
{
	struct thunder_mdio_softc *sc;
	uint64_t smi_cmd, smi_wr_dat;
	ssize_t timeout;

	sc = device_get_softc(dev);

	/* XXX Always C22 - for <= 1Gbps only */
	thunder_mdio_set_mode(sc, MODE_IEEE_C22);

	/* Prepare data for transmission */
	mdio_reg_write(sc, SMI_WR_DAT, data & SMI_WR_DAT_DAT_MASK);
	/*
	 * Assemble command
	 */
	smi_cmd = 0;
	/* Set opcode */
	if (sc->mode == MODE_IEEE_C22)
		smi_cmd |= SMI_CMD_PHY_OP_C22_WRITE;
	else
		smi_cmd |= SMI_CMD_PHY_OP_C45_WRITE;

	/* Set PHY address */
	smi_cmd |= ((phy << SMI_CMD_PHY_ADR_SHIFT) & SMI_CMD_PHY_ADR_MASK);
	/* Set PHY register offset */
	smi_cmd |= ((reg << SMI_CMD_PHY_REG_ADR_SHIFT) &
	    SMI_CMD_PHY_REG_ADR_MASK);

	mdio_reg_write(sc, SMI_CMD, smi_cmd);
	for (timeout = 1000; timeout > 0; timeout--) {
		smi_wr_dat = mdio_reg_read(sc, SMI_WR_DAT);
		if (smi_wr_dat & SMI_WR_DAT_PENDING)
			DELAY(1000);
		else
			break;
	}

	if (timeout <= 0)
		return (EIO);
	else {
		/* Return 0 on success */
		return (0);
	}
}