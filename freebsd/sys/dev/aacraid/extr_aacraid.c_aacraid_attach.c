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
typedef  int /*<<< orphan*/  u_int32_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct aac_softc {int flags; int /*<<< orphan*/  timeout_id; int /*<<< orphan*/  aac_io_lock; int /*<<< orphan*/  aac_daemontime; int /*<<< orphan*/  aac_state; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aac_sim_tqh; int /*<<< orphan*/ * eh; int /*<<< orphan*/  aifthread; TYPE_1__* aac_dev_t; int /*<<< orphan*/  aac_ev_cmfree; int /*<<< orphan*/  aac_container_tqh; int /*<<< orphan*/  msi_tupelo; int /*<<< orphan*/  msi_enabled; int /*<<< orphan*/  hint_flags; } ;
struct aac_mntinforesp {int MntRespCount; } ;
struct aac_fib {int dummy; } ;
struct TYPE_2__ {struct aac_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_ACCESS_DEVREG (struct aac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAC_ENABLE_INTERRUPT ; 
 int AAC_FLAGS_ENABLE_CAM ; 
 int AAC_FLAGS_SYNC_MODE ; 
 int AAC_MAX_CONTAINERS ; 
 int /*<<< orphan*/  AAC_STATE_SUSPEND ; 
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_DEFAULT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  aac_add_container (struct aac_softc*,struct aac_mntinforesp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aac_alloc (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_alloc_sync_fib (struct aac_softc*,struct aac_fib**) ; 
 int aac_check_firmware (struct aac_softc*) ; 
 scalar_t__ aac_command_thread ; 
 int /*<<< orphan*/  aac_container_bus (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_daemon ; 
 int /*<<< orphan*/  aac_define_int_mode (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_describe_controller (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_get_bus_info (struct aac_softc*) ; 
 scalar_t__ aac_get_container_info (struct aac_softc*,struct aac_fib*,int,struct aac_mntinforesp*,int /*<<< orphan*/ *) ; 
 int aac_init (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_initq_busy (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_initq_free (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_initq_ready (struct aac_softc*) ; 
 scalar_t__ aac_kthread_create (void (*) (void*),struct aac_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  aac_release_sync_fib (struct aac_softc*) ; 
 int aac_setup_intr (struct aac_softc*) ; 
 int /*<<< orphan*/  aacraid_cdevsw ; 
 int /*<<< orphan*/  aacraid_shutdown ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct aac_softc*) ; 
 int /*<<< orphan*/  device_get_flags (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int hz ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  timeout (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

int
aacraid_attach(struct aac_softc *sc)
{
	int error, unit;
	struct aac_fib *fib;
	struct aac_mntinforesp mir;
	int count = 0, i = 0;
	u_int32_t uid;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");
	sc->hint_flags = device_get_flags(sc->aac_dev);
	/*
	 * Initialize per-controller queues.
	 */
	aac_initq_free(sc);
	aac_initq_ready(sc);
	aac_initq_busy(sc);

	/* mark controller as suspended until we get ourselves organised */
	sc->aac_state |= AAC_STATE_SUSPEND;

	/*
	 * Check that the firmware on the card is supported.
	 */
	sc->msi_enabled = sc->msi_tupelo = FALSE;
	if ((error = aac_check_firmware(sc)) != 0)
		return(error);

	/*
	 * Initialize locks
	 */
	mtx_init(&sc->aac_io_lock, "AACRAID I/O lock", NULL, MTX_DEF);
	TAILQ_INIT(&sc->aac_container_tqh);
	TAILQ_INIT(&sc->aac_ev_cmfree);

#if __FreeBSD_version >= 800000
	/* Initialize the clock daemon callout. */
	callout_init_mtx(&sc->aac_daemontime, &sc->aac_io_lock, 0);
#endif
	/*
	 * Initialize the adapter.
	 */
	if ((error = aac_alloc(sc)) != 0)
		return(error);
	aac_define_int_mode(sc);
	if (!(sc->flags & AAC_FLAGS_SYNC_MODE)) {
		if ((error = aac_init(sc)) != 0)
			return(error);
	}

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
	 * Make the control device.
	 */
	unit = device_get_unit(sc->aac_dev);
	sc->aac_dev_t = make_dev(&aacraid_cdevsw, unit, UID_ROOT, GID_OPERATOR,
				 0640, "aacraid%d", unit);
	sc->aac_dev_t->si_drv1 = sc;

	/* Create the AIF thread */
	if (aac_kthread_create((void(*)(void *))aac_command_thread, sc,
		   &sc->aifthread, 0, 0, "aacraid%daif", unit))
		panic("Could not create AIF thread");

	/* Register the shutdown method to only be called post-dump */
	if ((sc->eh = EVENTHANDLER_REGISTER(shutdown_final, aacraid_shutdown,
	    sc->aac_dev, SHUTDOWN_PRI_DEFAULT)) == NULL)
		device_printf(sc->aac_dev,
			      "shutdown event registration failed\n");

	/* Find containers */
	mtx_lock(&sc->aac_io_lock);
	aac_alloc_sync_fib(sc, &fib);
	/* loop over possible containers */
	do {
		if ((aac_get_container_info(sc, fib, i, &mir, &uid)) != 0)
			continue;
		if (i == 0) 
			count = mir.MntRespCount;
		aac_add_container(sc, &mir, 0, uid);
		i++;
	} while ((i < count) && (i < AAC_MAX_CONTAINERS));
	aac_release_sync_fib(sc);
	mtx_unlock(&sc->aac_io_lock);

	/* Register with CAM for the containers */
	TAILQ_INIT(&sc->aac_sim_tqh);
	aac_container_bus(sc);
	/* Register with CAM for the non-DASD devices */
	if ((sc->flags & AAC_FLAGS_ENABLE_CAM) != 0) 
		aac_get_bus_info(sc);

	/* poke the bus to actually attach the child devices */
	bus_generic_attach(sc->aac_dev);

	/* mark the controller up */
	sc->aac_state &= ~AAC_STATE_SUSPEND;

	/* enable interrupts now */
	AAC_ACCESS_DEVREG(sc, AAC_ENABLE_INTERRUPT);

#if __FreeBSD_version >= 800000
	mtx_lock(&sc->aac_io_lock);
	callout_reset(&sc->aac_daemontime, 60 * hz, aac_daemon, sc);
	mtx_unlock(&sc->aac_io_lock);
#else
	{
		struct timeval tv;
		tv.tv_sec = 60;
		tv.tv_usec = 0;
		sc->timeout_id = timeout(aac_daemon, (void *)sc, tvtohz(&tv));
	}
#endif

	return(0);
}