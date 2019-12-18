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
struct rt_softc {int /*<<< orphan*/ * tx_ctx_idx; int /*<<< orphan*/ * tx_max_cnt; TYPE_1__* tx_ring; int /*<<< orphan*/ * tx_base_ptr; int /*<<< orphan*/  pdma_glo_cfg; int /*<<< orphan*/  tx_coherent_interrupts; } ;
struct TYPE_2__ {int desc_phys_addr; } ;

/* Variables and functions */
 int FE_TX_DMA_EN ; 
 int FE_TX_WB_DDONE ; 
 int /*<<< orphan*/  RT_DEBUG_INTR ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*) ; 
 int RT_READ (struct rt_softc*,int /*<<< orphan*/ ) ; 
 int RT_SOFTC_TX_RING_COUNT ; 
 int RT_SOFTC_TX_RING_DESC_COUNT ; 
 int /*<<< orphan*/  RT_WRITE (struct rt_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt_reset_tx_ring (struct rt_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  rt_txrx_enable (struct rt_softc*) ; 

__attribute__((used)) static void
rt_tx_coherent_intr(struct rt_softc *sc)
{
	uint32_t tmp;
	int i;

	RT_DPRINTF(sc, RT_DEBUG_INTR, "Tx coherent interrupt\n");

	sc->tx_coherent_interrupts++;

	/* restart DMA engine */
	tmp = RT_READ(sc, sc->pdma_glo_cfg);
	tmp &= ~(FE_TX_WB_DDONE | FE_TX_DMA_EN);
	RT_WRITE(sc, sc->pdma_glo_cfg, tmp);

	for (i = 0; i < RT_SOFTC_TX_RING_COUNT; i++)
		rt_reset_tx_ring(sc, &sc->tx_ring[i]);

	for (i = 0; i < RT_SOFTC_TX_RING_COUNT; i++) {
		RT_WRITE(sc, sc->tx_base_ptr[i],
			sc->tx_ring[i].desc_phys_addr);
		RT_WRITE(sc, sc->tx_max_cnt[i],
			RT_SOFTC_TX_RING_DESC_COUNT);
		RT_WRITE(sc, sc->tx_ctx_idx[i], 0);
	}

	rt_txrx_enable(sc);
}