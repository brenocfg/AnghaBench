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
struct mmc_data {int flags; scalar_t__ len; } ;
struct mmc_command {int error; TYPE_1__* mrq; struct mmc_data* data; } ;
struct aml8726_mmc_softc {int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmatag; struct mmc_command* cmd; int /*<<< orphan*/  ch; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* done ) (TYPE_1__*) ;struct mmc_command* stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_MMC_IRQ_STATUS_CLEAR_IRQ ; 
 int /*<<< orphan*/  AML_MMC_IRQ_STATUS_REG ; 
 int /*<<< orphan*/  AML_MMC_LOCK_ASSERT (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  AML_MMC_UNLOCK (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_mmc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MMC_DATA_READ ; 
 int MMC_DATA_WRITE ; 
 int MMC_ERR_NONE ; 
 int aml8726_mmc_start_command (struct aml8726_mmc_softc*,struct mmc_command*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
aml8726_mmc_finish_command(struct aml8726_mmc_softc *sc, int mmc_error)
{
	int mmc_stop_error;
	struct mmc_command *cmd;
	struct mmc_command *stop_cmd;
	struct mmc_data *data;

	AML_MMC_LOCK_ASSERT(sc);

	/* Clear all interrupts since the request is no longer in flight. */
	CSR_WRITE_4(sc, AML_MMC_IRQ_STATUS_REG, AML_MMC_IRQ_STATUS_CLEAR_IRQ);
	CSR_BARRIER(sc, AML_MMC_IRQ_STATUS_REG);

	/* In some cases (e.g. finish called via timeout) this is a NOP. */
	callout_stop(&sc->ch);

	cmd = sc->cmd;
	sc->cmd = NULL;

	cmd->error = mmc_error;

	data = cmd->data;

	if (data && data->len &&
	    (data->flags & (MMC_DATA_READ | MMC_DATA_WRITE)) != 0) {
		if ((data->flags & MMC_DATA_READ) != 0)
			bus_dmamap_sync(sc->dmatag, sc->dmamap,
			    BUS_DMASYNC_POSTREAD);
		else
			bus_dmamap_sync(sc->dmatag, sc->dmamap,
			    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->dmatag, sc->dmamap);
	}

	/*
	 * If there's a linked stop command, then start the stop command.
	 * In order to establish a known state attempt the stop command
	 * even if the original request encountered an error.
	 */

	stop_cmd = (cmd->mrq->stop != cmd) ? cmd->mrq->stop : NULL;

	if (stop_cmd != NULL) {
		mmc_stop_error = aml8726_mmc_start_command(sc, stop_cmd);
		if (mmc_stop_error == MMC_ERR_NONE) {
			AML_MMC_UNLOCK(sc);
			return;
		}
		stop_cmd->error = mmc_stop_error;
	}

	AML_MMC_UNLOCK(sc);

	/* Execute the callback after dropping the lock. */
	if (cmd->mrq)
		cmd->mrq->done(cmd->mrq);
}