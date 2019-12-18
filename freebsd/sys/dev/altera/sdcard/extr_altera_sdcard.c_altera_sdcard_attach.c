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
struct altera_sdcard_softc {int /*<<< orphan*/  as_task; int /*<<< orphan*/  as_taskqueue; int /*<<< orphan*/  as_unit; int /*<<< orphan*/  as_state; int /*<<< orphan*/ * as_currentbio; int /*<<< orphan*/  as_bioq; int /*<<< orphan*/ * as_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_SDCARD_CONDVAR_INIT (struct altera_sdcard_softc*) ; 
 int /*<<< orphan*/  ALTERA_SDCARD_LOCK_INIT (struct altera_sdcard_softc*) ; 
 int /*<<< orphan*/  ALTERA_SDCARD_STATE_NOCARD ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PI_DISK ; 
 int /*<<< orphan*/  TIMEOUT_TASK_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct altera_sdcard_softc*,int),struct altera_sdcard_softc*) ; 
 int /*<<< orphan*/  altera_sdcard_task (struct altera_sdcard_softc*,int) ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

void
altera_sdcard_attach(struct altera_sdcard_softc *sc)
{

	ALTERA_SDCARD_LOCK_INIT(sc);
	ALTERA_SDCARD_CONDVAR_INIT(sc);
	sc->as_disk = NULL;
	bioq_init(&sc->as_bioq);
	sc->as_currentbio = NULL;
	sc->as_state = ALTERA_SDCARD_STATE_NOCARD;
	sc->as_taskqueue = taskqueue_create("altera_sdcardc taskq", M_WAITOK,
	    taskqueue_thread_enqueue, &sc->as_taskqueue);
	taskqueue_start_threads(&sc->as_taskqueue, 1, PI_DISK,
	    "altera_sdcardc%d taskqueue", sc->as_unit);
	TIMEOUT_TASK_INIT(sc->as_taskqueue, &sc->as_task, 0,
	    altera_sdcard_task, sc);

	/*
	 * Kick off timer-driven processing with a manual poll so that we
	 * synchronously detect an already-inserted SD Card during the boot or
	 * other driver attach point.
	 */
	altera_sdcard_task(sc, 1);
}