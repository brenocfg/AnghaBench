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
typedef  int uint8_t ;
struct vr_softc {scalar_t__ vr_revid; } ;

/* Variables and functions */
 int CSR_READ_1 (struct vr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ REV_ID_VT6102_A ; 
 scalar_t__ REV_ID_VT6105_B0 ; 
 int /*<<< orphan*/  VR_LOCK_ASSERT (struct vr_softc*) ; 
 int /*<<< orphan*/  VR_PWRCFG_CLR ; 
 int VR_PWRCFG_WOLEN ; 
 int /*<<< orphan*/  VR_PWRCSR1_CLR ; 
 int /*<<< orphan*/  VR_PWRCSR_CLR ; 
 int /*<<< orphan*/  VR_STICKHW ; 
 int VR_STICKHW_DS0 ; 
 int VR_STICKHW_DS1 ; 
 int VR_STICKHW_WOL_ENB ; 
 int /*<<< orphan*/  VR_TESTREG_CLR ; 
 int /*<<< orphan*/  VR_WOLCFG_CLR ; 
 int VR_WOLCFG_PATTERN_PAGE ; 
 int VR_WOLCFG_PMEOVR ; 
 int VR_WOLCFG_SAB ; 
 int VR_WOLCFG_SAM ; 
 int /*<<< orphan*/  VR_WOLCR_CLR ; 

__attribute__((used)) static void
vr_clrwol(struct vr_softc *sc)
{
	uint8_t			v;

	VR_LOCK_ASSERT(sc);

	if (sc->vr_revid < REV_ID_VT6102_A)
		return;

	/* Take hardware out of sleep. */
	v = CSR_READ_1(sc, VR_STICKHW);
	v &= ~(VR_STICKHW_DS0 | VR_STICKHW_DS1 | VR_STICKHW_WOL_ENB);
	CSR_WRITE_1(sc, VR_STICKHW, v);

	/* Clear WOL configuration as WOL may interfere normal operation. */
	CSR_WRITE_1(sc, VR_WOLCR_CLR, 0xFF);
	CSR_WRITE_1(sc, VR_WOLCFG_CLR,
	    VR_WOLCFG_SAB | VR_WOLCFG_SAM | VR_WOLCFG_PMEOVR);
	CSR_WRITE_1(sc, VR_PWRCSR_CLR, 0xFF);
	CSR_WRITE_1(sc, VR_PWRCFG_CLR, VR_PWRCFG_WOLEN);
	if (sc->vr_revid > REV_ID_VT6105_B0) {
		/* Newer Rhine III supports two additional patterns. */
		CSR_WRITE_1(sc, VR_WOLCFG_CLR, VR_WOLCFG_PATTERN_PAGE);
		CSR_WRITE_1(sc, VR_TESTREG_CLR, 3);
		CSR_WRITE_1(sc, VR_PWRCSR1_CLR, 3);
	}
}