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
typedef  int uint8_t ;
struct smu_softc {scalar_t__ sc_doorbellirqid; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_cmdq; struct smu_cmd* sc_cur_cmd; } ;
struct smu_cmd {int cmd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct smu_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct smu_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_q ; 
 struct smu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smu_cmd ; 
 int /*<<< orphan*/  smu_doorbell_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_send_cmd (int /*<<< orphan*/ ,struct smu_cmd*) ; 
 int tsleep (struct smu_cmd*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
smu_run_cmd(device_t dev, struct smu_cmd *cmd, int wait)
{
	struct smu_softc *sc;
	uint8_t cmd_code;
	int error;

	sc = device_get_softc(dev);
	cmd_code = cmd->cmd;

	mtx_lock(&sc->sc_mtx);
	if (sc->sc_cur_cmd != NULL) {
		STAILQ_INSERT_TAIL(&sc->sc_cmdq, cmd, cmd_q);
	} else
		smu_send_cmd(dev, cmd);
	mtx_unlock(&sc->sc_mtx);

	if (!wait)
		return (0);

	if (sc->sc_doorbellirqid < 0) {
		/* Poll if the IRQ has not been set up yet */
		do {
			DELAY(50);
			smu_doorbell_intr(dev);
		} while (sc->sc_cur_cmd != NULL);
	} else {
		/* smu_doorbell_intr will wake us when the command is ACK'ed */
		error = tsleep(cmd, 0, "smu", 800 * hz / 1000);
		if (error != 0)
			smu_doorbell_intr(dev);	/* One last chance */
		
		if (error != 0) {
		    mtx_lock(&sc->sc_mtx);
		    if (cmd->cmd == cmd_code) {	/* Never processed */
			/* Abort this command if we timed out */
			if (sc->sc_cur_cmd == cmd)
				sc->sc_cur_cmd = NULL;
			else
				STAILQ_REMOVE(&sc->sc_cmdq, cmd, smu_cmd,
				    cmd_q);
			mtx_unlock(&sc->sc_mtx);
			return (error);
		    }
		    error = 0;
		    mtx_unlock(&sc->sc_mtx);
		}
	}

	/* SMU acks the command by inverting the command bits */
	if (cmd->cmd == ((~cmd_code) & 0xff))
		error = 0;
	else
		error = EIO;

	return (error);
}