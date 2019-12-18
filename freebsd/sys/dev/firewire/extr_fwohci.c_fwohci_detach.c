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
struct TYPE_2__ {int nisodma; int /*<<< orphan*/ * taskqueue; int /*<<< orphan*/  task_timeout; int /*<<< orphan*/ * config_rom; } ;
struct fwohci_softc {TYPE_1__ fc; int /*<<< orphan*/  fwohci_task_dma; int /*<<< orphan*/  fwohci_task_sid; int /*<<< orphan*/  fwohci_task_busreset; int /*<<< orphan*/ * ir; int /*<<< orphan*/ * it; int /*<<< orphan*/  atrs; int /*<<< orphan*/  atrq; int /*<<< orphan*/  arrs; int /*<<< orphan*/  arrq; int /*<<< orphan*/  crom_dma; int /*<<< orphan*/  sid_dma; int /*<<< orphan*/ * sid_buf; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  fwdma_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwohci_db_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

int
fwohci_detach(struct fwohci_softc *sc, device_t dev)
{
	int i;

	if (sc->sid_buf != NULL)
		fwdma_free(&sc->fc, &sc->sid_dma);
	if (sc->fc.config_rom != NULL)
		fwdma_free(&sc->fc, &sc->crom_dma);

	fwohci_db_free(&sc->arrq);
	fwohci_db_free(&sc->arrs);

	fwohci_db_free(&sc->atrq);
	fwohci_db_free(&sc->atrs);

	for (i = 0; i < sc->fc.nisodma; i++) {
		fwohci_db_free(&sc->it[i]);
		fwohci_db_free(&sc->ir[i]);
	}
	if (sc->fc.taskqueue != NULL) {
		taskqueue_drain(sc->fc.taskqueue, &sc->fwohci_task_busreset);
		taskqueue_drain(sc->fc.taskqueue, &sc->fwohci_task_sid);
		taskqueue_drain(sc->fc.taskqueue, &sc->fwohci_task_dma);
		taskqueue_drain(sc->fc.taskqueue, &sc->fc.task_timeout);
		taskqueue_free(sc->fc.taskqueue);
		sc->fc.taskqueue = NULL;
	}

	return 0;
}