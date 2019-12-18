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
struct ubsec_softc {int /*<<< orphan*/  sc_qchip2; int /*<<< orphan*/  sc_nqueue2; int /*<<< orphan*/  sc_queue2; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_paddr; } ;
struct ubsec_q2 {TYPE_1__ q_mcr; TYPE_1__ q_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_MCR2 ; 
 int /*<<< orphan*/  BS_STAT ; 
 int BS_STAT_MCR2_FULL ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int READ_REG (struct ubsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIMPLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ubsec_q2* SIMPLEQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIMPLEQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ubsec_q2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIMPLEQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG (struct ubsec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_next ; 
 int /*<<< orphan*/  ubsec_dma_sync (TYPE_1__*,int) ; 

__attribute__((used)) static int
ubsec_feed2(struct ubsec_softc *sc)
{
	struct ubsec_q2 *q;

	while (!SIMPLEQ_EMPTY(&sc->sc_queue2)) {
		if (READ_REG(sc, BS_STAT) & BS_STAT_MCR2_FULL)
			break;
		q = SIMPLEQ_FIRST(&sc->sc_queue2);

		ubsec_dma_sync(&q->q_mcr,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		ubsec_dma_sync(&q->q_ctx, BUS_DMASYNC_PREWRITE);

		WRITE_REG(sc, BS_MCR2, q->q_mcr.dma_paddr);
		SIMPLEQ_REMOVE_HEAD(&sc->sc_queue2, q_next);
		--sc->sc_nqueue2;
		SIMPLEQ_INSERT_TAIL(&sc->sc_qchip2, q, q_next);
	}
	return (0);
}