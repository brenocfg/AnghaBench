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
struct arswitch_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int AR934X_AT_CTRL_AGE_EN ; 
 int AR934X_AT_CTRL_LEARN_CHANGE ; 
 int /*<<< orphan*/  AR934X_QM_CTRL_ARP_COPY_EN ; 
 int /*<<< orphan*/  AR934X_QM_CTRL_ARP_EN ; 
 int /*<<< orphan*/  AR934X_REG_AT_CTRL ; 
 int /*<<< orphan*/  AR934X_REG_QM_CTRL ; 
 int /*<<< orphan*/  arswitch_modifyreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arswitch_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ar9340_atu_learn_default(struct arswitch_softc *sc)
{

	/* Enable aging, MAC replacing */
	arswitch_writereg(sc->sc_dev, AR934X_REG_AT_CTRL,
	    0x2b /* 5 min age time */ |
	    AR934X_AT_CTRL_AGE_EN |
	    AR934X_AT_CTRL_LEARN_CHANGE);

	/* Enable ARP frame acknowledge */
	arswitch_modifyreg(sc->sc_dev, AR934X_REG_QM_CTRL,
	    AR934X_QM_CTRL_ARP_EN, AR934X_QM_CTRL_ARP_EN);

#if 0
	/* Copy frame to CPU port, not just redirect it */
	arswitch_modifyreg(sc->sc_dev, AR934X_REG_QM_CTRL,
	    AR934X_QM_CTRL_ARP_COPY_EN, AR934X_QM_CTRL_ARP_COPY_EN);
#endif

	return (0);
}