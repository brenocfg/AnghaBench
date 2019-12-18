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
struct edma_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CERR_CAEI ; 
 int /*<<< orphan*/  DMA_CERR ; 
 int /*<<< orphan*/  DMA_ERR ; 
 int /*<<< orphan*/  DMA_ES ; 
 int READ4 (struct edma_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE1 (struct edma_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void
edma_err_intr(void *arg)
{
	struct edma_softc *sc;
	int reg;

	sc = arg;

	reg = READ4(sc, DMA_ERR);

#if 0
	device_printf(sc->dev, "DMA_ERR 0x%08x, ES 0x%08x\n",
	    reg, READ4(sc, DMA_ES));
#endif

	WRITE1(sc, DMA_CERR, CERR_CAEI);
}