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
struct mly_softc {int /*<<< orphan*/  mly_timeout; TYPE_1__* mly_dev_t; int /*<<< orphan*/  mly_dev; int /*<<< orphan*/  mly_task_complete; int /*<<< orphan*/  mly_lock; int /*<<< orphan*/  mly_periodic; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct mly_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_OPERATOR ; 
 int MLY_CMD_TIMEOUT ; 
 int /*<<< orphan*/  MLY_LOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_MASK_INTERRUPTS (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_UNLOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_UNMASK_INTERRUPTS (struct mly_softc*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mly_softc*) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct mly_softc*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct mly_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int hz ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int mly_alloc_commands (struct mly_softc*) ; 
 int mly_cam_attach (struct mly_softc*) ; 
 int /*<<< orphan*/  mly_cdevsw ; 
 int /*<<< orphan*/  mly_complete_handler ; 
 int /*<<< orphan*/  mly_describe_controller (struct mly_softc*) ; 
 int mly_enable_mmbox (struct mly_softc*) ; 
 int /*<<< orphan*/  mly_free (struct mly_softc*) ; 
 int mly_fwhandshake (struct mly_softc*) ; 
 int mly_get_controllerinfo (struct mly_softc*) ; 
 int mly_get_eventstatus (struct mly_softc*) ; 
 int /*<<< orphan*/  mly_initq_busy (struct mly_softc*) ; 
 int /*<<< orphan*/  mly_initq_complete (struct mly_softc*) ; 
 int /*<<< orphan*/  mly_initq_free (struct mly_softc*) ; 
 int mly_pci_attach (struct mly_softc*) ; 
 int /*<<< orphan*/  mly_periodic (void*) ; 
 int /*<<< orphan*/  mly_release_commands (struct mly_softc*) ; 
 int /*<<< orphan*/  mly_scan_devices (struct mly_softc*) ; 
 struct mly_softc* mly_softc0 ; 
 int /*<<< orphan*/  mly_timeout ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mly_attach(device_t dev)
{
    struct mly_softc	*sc = device_get_softc(dev);
    int			error;

    debug_called(1);

    sc->mly_dev = dev;
    mtx_init(&sc->mly_lock, "mly", NULL, MTX_DEF);
    callout_init_mtx(&sc->mly_periodic, &sc->mly_lock, 0);

#ifdef MLY_DEBUG
    callout_init_mtx(&sc->mly_timeout, &sc->mly_lock, 0);
    if (device_get_unit(sc->mly_dev) == 0)
	mly_softc0 = sc;
#endif    

    /*
     * Do PCI-specific initialisation.
     */
    if ((error = mly_pci_attach(sc)) != 0)
	goto out;

    /*
     * Initialise per-controller queues.
     */
    mly_initq_free(sc);
    mly_initq_busy(sc);
    mly_initq_complete(sc);

    /*
     * Initialise command-completion task.
     */
    TASK_INIT(&sc->mly_task_complete, 0, mly_complete_handler, sc);

    /* disable interrupts before we start talking to the controller */
    MLY_MASK_INTERRUPTS(sc);

    /* 
     * Wait for the controller to come ready, handshake with the firmware if required.
     * This is typically only necessary on platforms where the controller BIOS does not
     * run.
     */
    if ((error = mly_fwhandshake(sc)))
	goto out;

    /*
     * Allocate initial command buffers.
     */
    if ((error = mly_alloc_commands(sc)))
	goto out;

    /* 
     * Obtain controller feature information
     */
    MLY_LOCK(sc);
    error = mly_get_controllerinfo(sc);
    MLY_UNLOCK(sc);
    if (error)
	goto out;

    /*
     * Reallocate command buffers now we know how many we want.
     */
    mly_release_commands(sc);
    if ((error = mly_alloc_commands(sc)))
	goto out;

    /*
     * Get the current event counter for health purposes, populate the initial
     * health status buffer.
     */
    MLY_LOCK(sc);
    error = mly_get_eventstatus(sc);

    /*
     * Enable memory-mailbox mode.
     */
    if (error == 0)
	error = mly_enable_mmbox(sc);
    MLY_UNLOCK(sc);
    if (error)
	goto out;

    /*
     * Attach to CAM.
     */
    if ((error = mly_cam_attach(sc)))
	goto out;

    /* 
     * Print a little information about the controller 
     */
    mly_describe_controller(sc);

    /*
     * Mark all attached devices for rescan.
     */
    MLY_LOCK(sc);
    mly_scan_devices(sc);

    /*
     * Instigate the first status poll immediately.  Rescan completions won't
     * happen until interrupts are enabled, which should still be before
     * the SCSI subsystem gets to us, courtesy of the "SCSI settling delay".
     */
    mly_periodic((void *)sc);
    MLY_UNLOCK(sc);

    /*
     * Create the control device.
     */
    sc->mly_dev_t = make_dev(&mly_cdevsw, 0, UID_ROOT, GID_OPERATOR,
			     S_IRUSR | S_IWUSR, "mly%d", device_get_unit(sc->mly_dev));
    sc->mly_dev_t->si_drv1 = sc;

    /* enable interrupts now */
    MLY_UNMASK_INTERRUPTS(sc);

#ifdef MLY_DEBUG
    callout_reset(&sc->mly_timeout, MLY_CMD_TIMEOUT * hz, mly_timeout, sc);
#endif

 out:
    if (error != 0)
	mly_free(sc);
    return(error);
}