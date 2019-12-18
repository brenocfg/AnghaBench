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
struct vge_softc {struct ifnet* vge_ifp; int /*<<< orphan*/  vge_flags; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int CSR_READ_1 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int VGE_CR2_FDX_RXFLOWCTL_ENABLE ; 
 int VGE_CR2_FDX_TXFLOWCTL_ENABLE ; 
 int /*<<< orphan*/  VGE_CRC2 ; 
 int /*<<< orphan*/  VGE_CRS2 ; 
 int /*<<< orphan*/  VGE_FLAG_LINK ; 
 int /*<<< orphan*/  VGE_LOCK_ASSERT (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_PHYSTS0 ; 
 int VGE_PHYSTS_FDX ; 
 int VGE_PHYSTS_LINK ; 
 int VGE_PHYSTS_RESETSTS ; 
 int VGE_PHYSTS_RXFLOWCAP ; 
 int VGE_PHYSTS_TXFLOWCAP ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vge_miipoll_start (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
vge_link_statchg(void *xsc)
{
	struct vge_softc *sc;
	struct ifnet *ifp;
	uint8_t physts;

	sc = xsc;
	ifp = sc->vge_ifp;
	VGE_LOCK_ASSERT(sc);

	physts = CSR_READ_1(sc, VGE_PHYSTS0);
	if ((physts & VGE_PHYSTS_RESETSTS) == 0) {
		if ((physts & VGE_PHYSTS_LINK) == 0) {
			sc->vge_flags &= ~VGE_FLAG_LINK;
			if_link_state_change(sc->vge_ifp,
			    LINK_STATE_DOWN);
		} else {
			sc->vge_flags |= VGE_FLAG_LINK;
			if_link_state_change(sc->vge_ifp,
			    LINK_STATE_UP);
			CSR_WRITE_1(sc, VGE_CRC2, VGE_CR2_FDX_TXFLOWCTL_ENABLE |
			    VGE_CR2_FDX_RXFLOWCTL_ENABLE);
			if ((physts & VGE_PHYSTS_FDX) != 0) {
				if ((physts & VGE_PHYSTS_TXFLOWCAP) != 0)
					CSR_WRITE_1(sc, VGE_CRS2,
					    VGE_CR2_FDX_TXFLOWCTL_ENABLE);
				if ((physts & VGE_PHYSTS_RXFLOWCAP) != 0)
					CSR_WRITE_1(sc, VGE_CRS2,
					    VGE_CR2_FDX_RXFLOWCTL_ENABLE);
			}
			if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
				vge_start_locked(ifp);
		}
	}
	/*
	 * Restart MII auto-polling because link state change interrupt
	 * will disable it.
	 */
	vge_miipoll_start(sc);
}