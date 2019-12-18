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
struct TYPE_2__ {int* an_tx_fids; int an_tx_empty; scalar_t__ an_tx_cons; scalar_t__ an_tx_prod; scalar_t__* an_tx_ring; } ;
struct an_softc {TYPE_1__ an_rdata; int /*<<< orphan*/  mpi350; scalar_t__ an_gone; } ;

/* Variables and functions */
 int AN_TX_RING_CNT ; 
 int ENOMEM ; 
 scalar_t__ an_alloc_nicmem (struct an_softc*,int,int*) ; 

__attribute__((used)) static int
an_init_tx_ring(struct an_softc *sc)
{
	int			i;
	int			id;

	if (sc->an_gone)
		return (0);

	if (!sc->mpi350) {
		for (i = 0; i < AN_TX_RING_CNT; i++) {
			if (an_alloc_nicmem(sc, 1518 +
			    0x44, &id))
				return(ENOMEM);
			sc->an_rdata.an_tx_fids[i] = id;
			sc->an_rdata.an_tx_ring[i] = 0;
		}
	}

	sc->an_rdata.an_tx_prod = 0;
	sc->an_rdata.an_tx_cons = 0;
	sc->an_rdata.an_tx_empty = 1;

	return(0);
}