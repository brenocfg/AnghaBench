#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct aac_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct TYPE_5__ {int /*<<< orphan*/  buildNumber; } ;
struct aac_softc {int flags; int /*<<< orphan*/  aac_io_lock; int /*<<< orphan*/  aac_daemontime; int /*<<< orphan*/  aac_sim_tqh; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/ * eh; int /*<<< orphan*/  aifthread; TYPE_2__* aac_dev_t; TYPE_4__ aac_ich; TYPE_1__ aac_revision; int /*<<< orphan*/  aac_ev_cmfree; int /*<<< orphan*/  aac_container_tqh; int /*<<< orphan*/  aac_container_lock; int /*<<< orphan*/  aac_aifq_lock; int /*<<< orphan*/  aac_state; int /*<<< orphan*/  aac_task_complete; } ;
struct TYPE_6__ {struct aac_softc* si_drv1; } ;

/* Variables and functions */
 int AAC_FLAGS_ENABLE_CAM ; 
 int /*<<< orphan*/  AAC_STATE_SUSPEND ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int ENXIO ; 
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_DEFAULT ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aac_softc*) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int aac_alloc (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_cdevsw ; 
 int aac_check_firmware (struct aac_softc*) ; 
 scalar_t__ aac_command_thread ; 
 int /*<<< orphan*/  aac_complete ; 
 int /*<<< orphan*/  aac_daemon ; 
 int /*<<< orphan*/  aac_describe_controller (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_get_bus_info (struct aac_softc*) ; 
 int aac_init (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_initq_bio (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_initq_busy (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_initq_free (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_initq_ready (struct aac_softc*) ; 
 int aac_setup_intr (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_shutdown ; 
 int /*<<< orphan*/  aac_startup ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct aac_softc*) ; 
 scalar_t__ config_intrhook_establish (TYPE_4__*) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int hz ; 
 scalar_t__ kproc_create (void (*) (void*),struct aac_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  make_dev_alias (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  shutdown_final ; 

int
aac_attach(struct aac_softc *sc)
{
	int error, unit;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/*
	 * Initialize per-controller queues.
	 */
	aac_initq_free(sc);
	aac_initq_ready(sc);
	aac_initq_busy(sc);
	aac_initq_bio(sc);

	/*
	 * Initialize command-completion task.
	 */
	TASK_INIT(&sc->aac_task_complete, 0, aac_complete, sc);

	/* mark controller as suspended until we get ourselves organised */
	sc->aac_state |= AAC_STATE_SUSPEND;

	/*
	 * Check that the firmware on the card is supported.
	 */
	if ((error = aac_check_firmware(sc)) != 0)
		return(error);

	/*
	 * Initialize locks
	 */
	mtx_init(&sc->aac_aifq_lock, "AAC AIF lock", NULL, MTX_DEF);
	mtx_init(&sc->aac_io_lock, "AAC I/O lock", NULL, MTX_DEF);
	mtx_init(&sc->aac_container_lock, "AAC container lock", NULL, MTX_DEF);
	TAILQ_INIT(&sc->aac_container_tqh);
	TAILQ_INIT(&sc->aac_ev_cmfree);

	/* Initialize the clock daemon callout. */
	callout_init_mtx(&sc->aac_daemontime, &sc->aac_io_lock, 0);

	/*
	 * Initialize the adapter.
	 */
	if ((error = aac_alloc(sc)) != 0)
		return(error);
	if ((error = aac_init(sc)) != 0)
		return(error);

	/*
	 * Allocate and connect our interrupt.
	 */
	if ((error = aac_setup_intr(sc)) != 0)
		return(error);

	/*
	 * Print a little information about the controller.
	 */
	aac_describe_controller(sc);

	/*
	 * Add sysctls.
	 */
	SYSCTL_ADD_INT(device_get_sysctl_ctx(sc->aac_dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(sc->aac_dev)),
	    OID_AUTO, "firmware_build", CTLFLAG_RD,
	    &sc->aac_revision.buildNumber, 0,
	    "firmware build number");

	/*
	 * Register to probe our containers later.
	 */
	sc->aac_ich.ich_func = aac_startup;
	sc->aac_ich.ich_arg = sc;
	if (config_intrhook_establish(&sc->aac_ich) != 0) {
		device_printf(sc->aac_dev,
			      "can't establish configuration hook\n");
		return(ENXIO);
	}

	/*
	 * Make the control device.
	 */
	unit = device_get_unit(sc->aac_dev);
	sc->aac_dev_t = make_dev(&aac_cdevsw, unit, UID_ROOT, GID_OPERATOR,
				 0640, "aac%d", unit);
	(void)make_dev_alias(sc->aac_dev_t, "afa%d", unit);
	(void)make_dev_alias(sc->aac_dev_t, "hpn%d", unit);
	sc->aac_dev_t->si_drv1 = sc;

	/* Create the AIF thread */
	if (kproc_create((void(*)(void *))aac_command_thread, sc,
		   &sc->aifthread, 0, 0, "aac%daif", unit))
		panic("Could not create AIF thread");

	/* Register the shutdown method to only be called post-dump */
	if ((sc->eh = EVENTHANDLER_REGISTER(shutdown_final, aac_shutdown,
	    sc->aac_dev, SHUTDOWN_PRI_DEFAULT)) == NULL)
		device_printf(sc->aac_dev,
			      "shutdown event registration failed\n");

	/* Register with CAM for the non-DASD devices */
	if ((sc->flags & AAC_FLAGS_ENABLE_CAM) != 0) {
		TAILQ_INIT(&sc->aac_sim_tqh);
		aac_get_bus_info(sc);
	}

	mtx_lock(&sc->aac_io_lock);
	callout_reset(&sc->aac_daemontime, 60 * hz, aac_daemon, sc);
	mtx_unlock(&sc->aac_io_lock);

	return(0);
}