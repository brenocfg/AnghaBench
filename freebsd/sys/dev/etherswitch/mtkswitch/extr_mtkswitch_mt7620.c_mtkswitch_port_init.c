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
struct TYPE_2__ {int (* mtkswitch_read ) (struct mtkswitch_softc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* mtkswitch_write ) (struct mtkswitch_softc*,int /*<<< orphan*/ ,int) ;} ;
struct mtkswitch_softc {int cpuport; TYPE_1__ hal; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTKSWITCH_PCR (int) ; 
 int /*<<< orphan*/  MTKSWITCH_PMCR (int) ; 
 int /*<<< orphan*/  MTKSWITCH_PVC (int) ; 
 int PCR_PORT_VLAN_SECURE ; 
 int PMCR_CFG_DEFAULT ; 
 int PMCR_FORCE_DPX ; 
 int PMCR_FORCE_LINK ; 
 int PMCR_FORCE_MODE ; 
 int PMCR_FORCE_SPD_1000 ; 
 int PVC_VLAN_ATTR_MASK ; 
 int stub1 (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtkswitch_softc*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct mtkswitch_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct mtkswitch_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mtkswitch_port_init(struct mtkswitch_softc *sc, int port)
{
	uint32_t val;

	/* Called early and hence unlocked */

	/* Set the port to secure mode */
	val = sc->hal.mtkswitch_read(sc, MTKSWITCH_PCR(port));
	val |= PCR_PORT_VLAN_SECURE;
	sc->hal.mtkswitch_write(sc, MTKSWITCH_PCR(port), val);

	/* Set port's vlan_attr to user port */
	val = sc->hal.mtkswitch_read(sc, MTKSWITCH_PVC(port));
	val &= ~PVC_VLAN_ATTR_MASK;
	sc->hal.mtkswitch_write(sc, MTKSWITCH_PVC(port), val);

	val = PMCR_CFG_DEFAULT;
	if (port == sc->cpuport)
		val |= PMCR_FORCE_LINK | PMCR_FORCE_DPX | PMCR_FORCE_SPD_1000 |
		    PMCR_FORCE_MODE;
	/* Set port's MAC to default settings */
	sc->hal.mtkswitch_write(sc, MTKSWITCH_PMCR(port), val);
}