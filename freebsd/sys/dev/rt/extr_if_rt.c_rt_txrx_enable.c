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
typedef  int uint32_t ;
struct rt_softc {int /*<<< orphan*/  pdma_glo_cfg; int /*<<< orphan*/  dev; struct ifnet* ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int FE_RX_DMA_BUSY ; 
 int FE_RX_DMA_EN ; 
 int FE_TX_DMA_BUSY ; 
 int FE_TX_DMA_EN ; 
 int FE_TX_WB_DDONE ; 
 int RT_READ (struct rt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_WRITE (struct rt_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
rt_txrx_enable(struct rt_softc *sc)
{
	struct ifnet *ifp;
	uint32_t tmp;
	int ntries;

	ifp = sc->ifp;

	/* enable Tx/Rx DMA engine */
	for (ntries = 0; ntries < 200; ntries++) {
		tmp = RT_READ(sc, sc->pdma_glo_cfg);
		if (!(tmp & (FE_TX_DMA_BUSY | FE_RX_DMA_BUSY)))
			break;

		DELAY(1000);
	}

	if (ntries == 200) {
		device_printf(sc->dev, "timeout waiting for DMA engine\n");
		return (-1);
	}

	DELAY(50);

	tmp |= FE_TX_WB_DDONE |	FE_RX_DMA_EN | FE_TX_DMA_EN;
	RT_WRITE(sc, sc->pdma_glo_cfg, tmp);

	/* XXX set Rx filter */
	return (0);
}