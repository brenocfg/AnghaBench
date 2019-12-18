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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ue_dev; } ;
struct muge_softc {scalar_t__ sc_mdix_ctl; int /*<<< orphan*/  sc_phyno; TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MUGE_EXT_MODE_CTRL ; 
 scalar_t__ MUGE_EXT_MODE_CTRL_AUTO_MDIX_ ; 
 scalar_t__ MUGE_EXT_MODE_CTRL_MDIX_MASK_ ; 
 int /*<<< orphan*/  MUGE_EXT_PAGE_ACCESS ; 
 scalar_t__ MUGE_EXT_PAGE_SPACE_0 ; 
 scalar_t__ MUGE_EXT_PAGE_SPACE_1 ; 
 scalar_t__ lan78xx_miibus_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lan78xx_miibus_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  muge_warn_printf (struct muge_softc*,char*) ; 

__attribute__((used)) static void
lan78xx_set_mdix_auto(struct muge_softc *sc)
{
	uint32_t buf, err;

	err = lan78xx_miibus_writereg(sc->sc_ue.ue_dev, sc->sc_phyno,
	    MUGE_EXT_PAGE_ACCESS, MUGE_EXT_PAGE_SPACE_1);

	buf = lan78xx_miibus_readreg(sc->sc_ue.ue_dev, sc->sc_phyno,
	    MUGE_EXT_MODE_CTRL);
	buf &= ~MUGE_EXT_MODE_CTRL_MDIX_MASK_;
	buf |= MUGE_EXT_MODE_CTRL_AUTO_MDIX_;

	lan78xx_miibus_readreg(sc->sc_ue.ue_dev, sc->sc_phyno, MII_BMCR);
	err += lan78xx_miibus_writereg(sc->sc_ue.ue_dev, sc->sc_phyno,
	    MUGE_EXT_MODE_CTRL, buf);

	err += lan78xx_miibus_writereg(sc->sc_ue.ue_dev, sc->sc_phyno,
	    MUGE_EXT_PAGE_ACCESS, MUGE_EXT_PAGE_SPACE_0);

	if (err != 0)
		muge_warn_printf(sc, "error setting PHY's MDIX status\n");

	sc->sc_mdix_ctl = buf;
}