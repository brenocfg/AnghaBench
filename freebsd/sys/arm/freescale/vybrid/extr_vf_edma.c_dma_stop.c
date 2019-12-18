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
struct edma_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ERQ ; 
 int READ4 (struct edma_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct edma_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dma_stop(struct edma_softc *sc, int chnum)
{
	int reg;

	reg = READ4(sc, DMA_ERQ);
	reg &= ~(0x1 << chnum);
	WRITE4(sc, DMA_ERQ, reg);

	return (0);
}