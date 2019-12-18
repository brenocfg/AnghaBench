#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vge_rx_commit; struct vge_rxdesc* vge_rxdesc; } ;
struct vge_softc {TYPE_2__ vge_cdata; } ;
struct vge_rxdesc {struct vge_rxdesc* rxd_prev; TYPE_1__* rx_desc; } ;
struct TYPE_3__ {scalar_t__ vge_sts; scalar_t__ vge_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGE_RDSTS_OWN ; 
 int VGE_RXCHUNK ; 
 scalar_t__ htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vge_discard_rxbuf(struct vge_softc *sc, int prod)
{
	struct vge_rxdesc *rxd;
	int i;

	rxd = &sc->vge_cdata.vge_rxdesc[prod];
	rxd->rx_desc->vge_sts = 0;
	rxd->rx_desc->vge_ctl = 0;

	/*
	 * Note: the manual fails to document the fact that for
	 * proper opration, the driver needs to replentish the RX
	 * DMA ring 4 descriptors at a time (rather than one at a
	 * time, like most chips). We can allocate the new buffers
	 * but we should not set the OWN bits until we're ready
	 * to hand back 4 of them in one shot.
	 */
	if ((prod % VGE_RXCHUNK) == (VGE_RXCHUNK - 1)) {
		for (i = VGE_RXCHUNK; i > 0; i--) {
			rxd->rx_desc->vge_sts = htole32(VGE_RDSTS_OWN);
			rxd = rxd->rxd_prev;
		}
		sc->vge_cdata.vge_rx_commit += VGE_RXCHUNK;
	}
}