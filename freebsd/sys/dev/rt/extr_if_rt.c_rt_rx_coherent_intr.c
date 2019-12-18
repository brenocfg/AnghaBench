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
struct rt_softc {int rx_ring_count; int /*<<< orphan*/ * rx_calc_idx; int /*<<< orphan*/ * rx_max_cnt; TYPE_1__* rx_ring; int /*<<< orphan*/ * rx_base_ptr; int /*<<< orphan*/  pdma_glo_cfg; int /*<<< orphan*/  rx_coherent_interrupts; } ;
struct TYPE_2__ {int desc_phys_addr; } ;

/* Variables and functions */
 int FE_RX_DMA_EN ; 
 int /*<<< orphan*/  RT_DEBUG_INTR ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*) ; 
 int RT_READ (struct rt_softc*,int /*<<< orphan*/ ) ; 
 int RT_SOFTC_RX_RING_DATA_COUNT ; 
 int /*<<< orphan*/  RT_WRITE (struct rt_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt_reset_rx_ring (struct rt_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  rt_txrx_enable (struct rt_softc*) ; 

__attribute__((used)) static void
rt_rx_coherent_intr(struct rt_softc *sc)
{
	uint32_t tmp;
	int i;

	RT_DPRINTF(sc, RT_DEBUG_INTR, "Rx coherent interrupt\n");

	sc->rx_coherent_interrupts++;

	/* restart DMA engine */
	tmp = RT_READ(sc, sc->pdma_glo_cfg);
	tmp &= ~(FE_RX_DMA_EN);
	RT_WRITE(sc, sc->pdma_glo_cfg, tmp);

	/* init Rx ring */
	for (i = 0; i < sc->rx_ring_count; i++)
		rt_reset_rx_ring(sc, &sc->rx_ring[i]);

	for (i = 0; i < sc->rx_ring_count; i++) {
		RT_WRITE(sc, sc->rx_base_ptr[i],
			sc->rx_ring[i].desc_phys_addr);
		RT_WRITE(sc, sc->rx_max_cnt[i],
			RT_SOFTC_RX_RING_DATA_COUNT);
		RT_WRITE(sc, sc->rx_calc_idx[i],
			RT_SOFTC_RX_RING_DATA_COUNT - 1);
	}

	rt_txrx_enable(sc);
}