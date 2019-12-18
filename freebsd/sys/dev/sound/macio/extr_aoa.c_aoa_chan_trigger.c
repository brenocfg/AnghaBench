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
struct aoa_dma {int running; int slots; int /*<<< orphan*/  mutex; int /*<<< orphan*/  channel; int /*<<< orphan*/  slot; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
#define  PCMTRIG_ABORT 130 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  dbdma_clear_cmd_status (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbdma_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_set_current_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_set_device_status (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dbdma_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aoa_chan_trigger(kobj_t obj, void *data, int go)
{
	struct aoa_dma 	*dma = data;
	int 		 i;

	switch (go) {
	case PCMTRIG_START:

		/* Start the DMA. */
		dma->running = 1;
		
		dma->slot = 0;
		dbdma_set_current_cmd(dma->channel, dma->slot);

		dbdma_run(dma->channel);

		return (0);

	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
		
		mtx_lock(&dma->mutex);

		dma->running = 0;

		/* Make it branch to the STOP command. */
		dbdma_set_device_status(dma->channel, 1 << 0, 1 << 0);

		/* XXX should wait for DBDMA_ACTIVE to clear. */
		DELAY(40000);

		/* Reset the DMA. */
		dbdma_stop(dma->channel);
		dbdma_set_device_status(dma->channel, 1 << 0, 0);

		for (i = 0; i < dma->slots; ++i)
			dbdma_clear_cmd_status(dma->channel, i);

		mtx_unlock(&dma->mutex);

		return (0);
	}

	return (0);
}