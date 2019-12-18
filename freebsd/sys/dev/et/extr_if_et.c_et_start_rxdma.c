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
struct et_softc {int /*<<< orphan*/  ifp; TYPE_1__* sc_rx_data; } ;
struct TYPE_2__ {int rbd_bufsize; } ;

/* Variables and functions */
 int CSR_READ_4 (struct et_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ET_RXDMA_CTRL ; 
 int ET_RXDMA_CTRL_HALTED ; 
 int ET_RXDMA_CTRL_RING0_ENABLE ; 
 int ET_RXDMA_CTRL_RING0_SIZE_MASK ; 
 int ET_RXDMA_CTRL_RING1_ENABLE ; 
 int ET_RXDMA_CTRL_RING1_SIZE_MASK ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
et_start_rxdma(struct et_softc *sc)
{
	uint32_t val;

	val = (sc->sc_rx_data[0].rbd_bufsize & ET_RXDMA_CTRL_RING0_SIZE_MASK) |
	    ET_RXDMA_CTRL_RING0_ENABLE;
	val |= (sc->sc_rx_data[1].rbd_bufsize & ET_RXDMA_CTRL_RING1_SIZE_MASK) |
	    ET_RXDMA_CTRL_RING1_ENABLE;

	CSR_WRITE_4(sc, ET_RXDMA_CTRL, val);

	DELAY(5);

	if (CSR_READ_4(sc, ET_RXDMA_CTRL) & ET_RXDMA_CTRL_HALTED) {
		if_printf(sc->ifp, "can't start RX DMA engine\n");
		return (ETIMEDOUT);
	}
	return (0);
}