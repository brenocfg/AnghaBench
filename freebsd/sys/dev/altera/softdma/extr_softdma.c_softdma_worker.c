#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ transferred; scalar_t__ error; } ;
typedef  TYPE_1__ xdma_transfer_status_t ;
struct softdma_softc {int dummy; } ;
struct softdma_channel {scalar_t__ run; int /*<<< orphan*/  mtx; int /*<<< orphan*/  xchan; struct softdma_softc* sc; } ;

/* Variables and functions */
 int hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (struct softdma_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  softdma_process_descriptors (struct softdma_channel*,TYPE_1__*) ; 
 int /*<<< orphan*/  xdma_callback (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
softdma_worker(void *arg)
{
	xdma_transfer_status_t status;
	struct softdma_channel *chan;
	struct softdma_softc *sc;

	chan = arg;

	sc = chan->sc;

	while (1) {
		mtx_lock(&chan->mtx);

		do {
			mtx_sleep(chan, &chan->mtx, 0, "softdma_wait", hz / 2);
		} while (chan->run == 0);

		status.error = 0;
		status.transferred = 0;

		softdma_process_descriptors(chan, &status);

		/* Finish operation */
		chan->run = 0;
		xdma_callback(chan->xchan, &status);

		mtx_unlock(&chan->mtx);
	}

}