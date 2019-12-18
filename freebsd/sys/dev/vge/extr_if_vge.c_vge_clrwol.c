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
struct vge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_CLRBIT_1 (struct vge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CSR_READ_1 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VGE_DIAGCTL ; 
 int /*<<< orphan*/  VGE_DIAGCTL_GMII ; 
 int /*<<< orphan*/  VGE_DIAGCTL_MACFORCE ; 
 int /*<<< orphan*/  VGE_PWRSTAT ; 
 int VGE_STICKHW_DS0 ; 
 int VGE_STICKHW_DS1 ; 
 int VGE_STICKHW_SWPTAG ; 
 int /*<<< orphan*/  VGE_WOLCFGC ; 
 int VGE_WOLCFG_PMEOVR ; 
 int VGE_WOLCFG_SAB ; 
 int VGE_WOLCFG_SAM ; 
 int /*<<< orphan*/  VGE_WOLCR0C ; 
 int VGE_WOLCR0_PATTERN_ALL ; 
 int /*<<< orphan*/  VGE_WOLCR1C ; 
 int /*<<< orphan*/  VGE_WOLSR0C ; 
 int /*<<< orphan*/  VGE_WOLSR1C ; 

__attribute__((used)) static void
vge_clrwol(struct vge_softc *sc)
{
	uint8_t val;

	val = CSR_READ_1(sc, VGE_PWRSTAT);
	val &= ~VGE_STICKHW_SWPTAG;
	CSR_WRITE_1(sc, VGE_PWRSTAT, val);
	/* Disable WOL and clear power state indicator. */
	val = CSR_READ_1(sc, VGE_PWRSTAT);
	val &= ~(VGE_STICKHW_DS0 | VGE_STICKHW_DS1);
	CSR_WRITE_1(sc, VGE_PWRSTAT, val);

	CSR_CLRBIT_1(sc, VGE_DIAGCTL, VGE_DIAGCTL_GMII);
	CSR_CLRBIT_1(sc, VGE_DIAGCTL, VGE_DIAGCTL_MACFORCE);

	/* Clear WOL on pattern match. */
	CSR_WRITE_1(sc, VGE_WOLCR0C, VGE_WOLCR0_PATTERN_ALL);
	/* Disable WOL on magic/unicast packet. */
	CSR_WRITE_1(sc, VGE_WOLCR1C, 0x0F);
	CSR_WRITE_1(sc, VGE_WOLCFGC, VGE_WOLCFG_SAB | VGE_WOLCFG_SAM |
	    VGE_WOLCFG_PMEOVR);
	/* Clear WOL status on pattern match. */
	CSR_WRITE_1(sc, VGE_WOLSR0C, 0xFF);
	CSR_WRITE_1(sc, VGE_WOLSR1C, 0xFF);
}