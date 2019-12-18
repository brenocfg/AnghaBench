#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ version; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ig4iic_softc_t ;

/* Variables and functions */
 scalar_t__ IG4_ATOM ; 
 scalar_t__ IG4_HASWELL ; 
 scalar_t__ IG4_HAS_ADDREGS (scalar_t__) ; 
 int /*<<< orphan*/  IG4_REG_ACTIVE_LTR_VALUE ; 
 int /*<<< orphan*/  IG4_REG_AUTO_LTR_VALUE ; 
 int /*<<< orphan*/  IG4_REG_CLK_PARMS ; 
 int /*<<< orphan*/  IG4_REG_COMP_PARAM1 ; 
 int /*<<< orphan*/  IG4_REG_COMP_TYPE ; 
 int /*<<< orphan*/  IG4_REG_COMP_VER ; 
 int /*<<< orphan*/  IG4_REG_CTL ; 
 int /*<<< orphan*/  IG4_REG_DMA_CTRL ; 
 int /*<<< orphan*/  IG4_REG_DMA_RDLR ; 
 int /*<<< orphan*/  IG4_REG_DMA_TDLR ; 
 int /*<<< orphan*/  IG4_REG_ENABLE_STATUS ; 
 int /*<<< orphan*/  IG4_REG_FS_SCL_HCNT ; 
 int /*<<< orphan*/  IG4_REG_FS_SCL_LCNT ; 
 int /*<<< orphan*/  IG4_REG_GENERAL ; 
 int /*<<< orphan*/  IG4_REG_I2C_EN ; 
 int /*<<< orphan*/  IG4_REG_I2C_STA ; 
 int /*<<< orphan*/  IG4_REG_IDLE_LTR_VALUE ; 
 int /*<<< orphan*/  IG4_REG_INTR_MASK ; 
 int /*<<< orphan*/  IG4_REG_INTR_STAT ; 
 int /*<<< orphan*/  IG4_REG_RAW_INTR_STAT ; 
 int /*<<< orphan*/  IG4_REG_RESETS_HSW ; 
 int /*<<< orphan*/  IG4_REG_RESETS_SKL ; 
 int /*<<< orphan*/  IG4_REG_RXFLR ; 
 int /*<<< orphan*/  IG4_REG_RX_TL ; 
 int /*<<< orphan*/  IG4_REG_SDA_HOLD ; 
 int /*<<< orphan*/  IG4_REG_SDA_SETUP ; 
 int /*<<< orphan*/  IG4_REG_SLV_DATA_NACK ; 
 int /*<<< orphan*/  IG4_REG_SS_SCL_HCNT ; 
 int /*<<< orphan*/  IG4_REG_SS_SCL_LCNT ; 
 int /*<<< orphan*/  IG4_REG_SW_LTR_VALUE ; 
 int /*<<< orphan*/  IG4_REG_TAR_ADD ; 
 int /*<<< orphan*/  IG4_REG_TXFLR ; 
 int /*<<< orphan*/  IG4_REG_TX_ABRT_SOURCE ; 
 int /*<<< orphan*/  IG4_REG_TX_TL ; 
 scalar_t__ IG4_SKYLAKE ; 
 int /*<<< orphan*/  REGDUMP (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ig4iic_dump(ig4iic_softc_t *sc)
{
	device_printf(sc->dev, "ig4iic register dump:\n");
	REGDUMP(sc, IG4_REG_CTL);
	REGDUMP(sc, IG4_REG_TAR_ADD);
	REGDUMP(sc, IG4_REG_SS_SCL_HCNT);
	REGDUMP(sc, IG4_REG_SS_SCL_LCNT);
	REGDUMP(sc, IG4_REG_FS_SCL_HCNT);
	REGDUMP(sc, IG4_REG_FS_SCL_LCNT);
	REGDUMP(sc, IG4_REG_INTR_STAT);
	REGDUMP(sc, IG4_REG_INTR_MASK);
	REGDUMP(sc, IG4_REG_RAW_INTR_STAT);
	REGDUMP(sc, IG4_REG_RX_TL);
	REGDUMP(sc, IG4_REG_TX_TL);
	REGDUMP(sc, IG4_REG_I2C_EN);
	REGDUMP(sc, IG4_REG_I2C_STA);
	REGDUMP(sc, IG4_REG_TXFLR);
	REGDUMP(sc, IG4_REG_RXFLR);
	REGDUMP(sc, IG4_REG_SDA_HOLD);
	REGDUMP(sc, IG4_REG_TX_ABRT_SOURCE);
	REGDUMP(sc, IG4_REG_SLV_DATA_NACK);
	REGDUMP(sc, IG4_REG_DMA_CTRL);
	REGDUMP(sc, IG4_REG_DMA_TDLR);
	REGDUMP(sc, IG4_REG_DMA_RDLR);
	REGDUMP(sc, IG4_REG_SDA_SETUP);
	REGDUMP(sc, IG4_REG_ENABLE_STATUS);
	REGDUMP(sc, IG4_REG_COMP_PARAM1);
	REGDUMP(sc, IG4_REG_COMP_VER);
	if (sc->version == IG4_ATOM) {
		REGDUMP(sc, IG4_REG_COMP_TYPE);
		REGDUMP(sc, IG4_REG_CLK_PARMS);
	}
	if (sc->version == IG4_HASWELL || sc->version == IG4_ATOM) {
		REGDUMP(sc, IG4_REG_RESETS_HSW);
		REGDUMP(sc, IG4_REG_GENERAL);
	} else if (sc->version == IG4_SKYLAKE) {
		REGDUMP(sc, IG4_REG_RESETS_SKL);
	}
	if (sc->version == IG4_HASWELL) {
		REGDUMP(sc, IG4_REG_SW_LTR_VALUE);
		REGDUMP(sc, IG4_REG_AUTO_LTR_VALUE);
	} else if (IG4_HAS_ADDREGS(sc->version)) {
		REGDUMP(sc, IG4_REG_ACTIVE_LTR_VALUE);
		REGDUMP(sc, IG4_REG_IDLE_LTR_VALUE);
	}
}