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
struct aoa_softc {struct aoa_dma* sc_intrp; } ;
struct aoa_dma {int slot; int slots; int /*<<< orphan*/  mutex; int /*<<< orphan*/  pcm; int /*<<< orphan*/  channel; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_clear_cmd_status (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dbdma_get_cmd_status (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void 
aoa_interrupt(void *xsc)
{
	struct aoa_softc	*sc = xsc;
	struct aoa_dma		*dma;

	if (!(dma = sc->sc_intrp) || !dma->running)
		return;

	mtx_lock(&dma->mutex);

	while (dbdma_get_cmd_status(dma->channel, dma->slot)) {

		dbdma_clear_cmd_status(dma->channel, dma->slot);
		dma->slot = (dma->slot + 1) % dma->slots;

		mtx_unlock(&dma->mutex);
		chn_intr(dma->pcm);
		mtx_lock(&dma->mutex);
	}

	mtx_unlock(&dma->mutex);
}