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
struct et_softc {int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int CSR_READ_4 (struct et_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ET_RXDMA_CTRL ; 
 int ET_RXDMA_CTRL_HALT ; 
 int ET_RXDMA_CTRL_HALTED ; 
 int ET_RXDMA_CTRL_RING1_ENABLE ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
et_stop_rxdma(struct et_softc *sc)
{

	CSR_WRITE_4(sc, ET_RXDMA_CTRL,
		    ET_RXDMA_CTRL_HALT | ET_RXDMA_CTRL_RING1_ENABLE);

	DELAY(5);
	if ((CSR_READ_4(sc, ET_RXDMA_CTRL) & ET_RXDMA_CTRL_HALTED) == 0) {
		if_printf(sc->ifp, "can't stop RX DMA engine\n");
		return (ETIMEDOUT);
	}
	return (0);
}