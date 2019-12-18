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
struct TYPE_4__ {int /*<<< orphan*/ * bge_rx_std_seglen; } ;
struct TYPE_3__ {struct bge_rx_bd* bge_rx_std_ring; } ;
struct bge_softc {size_t bge_std; TYPE_2__ bge_cdata; TYPE_1__ bge_ldata; } ;
struct bge_rx_bd {int bge_idx; int /*<<< orphan*/  bge_len; int /*<<< orphan*/  bge_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_INC (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_RXBDFLAG_END ; 
 int /*<<< orphan*/  BGE_STD_RX_RING_CNT ; 

__attribute__((used)) static __inline void
bge_rxreuse_std(struct bge_softc *sc, int i)
{
	struct bge_rx_bd *r;

	r = &sc->bge_ldata.bge_rx_std_ring[sc->bge_std];
	r->bge_flags = BGE_RXBDFLAG_END;
	r->bge_len = sc->bge_cdata.bge_rx_std_seglen[i];
	r->bge_idx = i;
	BGE_INC(sc->bge_std, BGE_STD_RX_RING_CNT);
}