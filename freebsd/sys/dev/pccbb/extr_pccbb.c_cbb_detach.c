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
struct cbb_softc {int flags; int /*<<< orphan*/  mtx; int /*<<< orphan*/  base_res; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  event_thread; int /*<<< orphan*/  intrhand; int /*<<< orphan*/  dev; int /*<<< orphan*/ * exca; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_OFF ; 
 int /*<<< orphan*/  CBBR_SOCKBASE ; 
 int CBB_KTHREAD_DONE ; 
 int CBB_KTHREAD_RUNNING ; 
 int /*<<< orphan*/  CBB_SOCKET_EVENT ; 
 int /*<<< orphan*/  CBB_SOCKET_MASK ; 
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXCA_INTR ; 
 int /*<<< orphan*/  EXCA_INTR_RESET ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_set (struct cbb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exca_clrb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
cbb_detach(device_t brdev)
{
	struct cbb_softc *sc = device_get_softc(brdev);
	device_t *devlist;
	int tmp, tries, error, numdevs;

	/*
	 * Before we delete the children (which we have to do because
	 * attach doesn't check for children busses correctly), we have
	 * to detach the children.  Even if we didn't need to delete the
	 * children, we have to detach them.
	 */
	error = bus_generic_detach(brdev);
	if (error != 0)
		return (error);

	/*
	 * Since the attach routine doesn't search for children before it
	 * attaches them to this device, we must delete them here in order
	 * for the kldload/unload case to work.  If we failed to do that, then
	 * we'd get duplicate devices when cbb.ko was reloaded.
	 */
	tries = 10;
	do {
		error = device_get_children(brdev, &devlist, &numdevs);
		if (error == 0)
			break;
		/*
		 * Try hard to cope with low memory.
		 */
		if (error == ENOMEM) {
			pause("cbbnomem", 1);
			continue;
		}
	} while (tries-- > 0);
	for (tmp = 0; tmp < numdevs; tmp++)
		device_delete_child(brdev, devlist[tmp]);
	free(devlist, M_TEMP);

	/* Turn off the interrupts */
	cbb_set(sc, CBB_SOCKET_MASK, 0);

	/* reset 16-bit pcmcia bus */
	exca_clrb(&sc->exca[0], EXCA_INTR, EXCA_INTR_RESET);

	/* turn off power */
	cbb_power(brdev, CARD_OFF);

	/* Ack the interrupt */
	cbb_set(sc, CBB_SOCKET_EVENT, 0xffffffff);

	/*
	 * Wait for the thread to die.  kproc_exit will do a wakeup
	 * on the event thread's struct proc * so that we know it is
	 * safe to proceed.  IF the thread is running, set the please
	 * die flag and wait for it to comply.  Since the wakeup on
	 * the event thread happens only in kproc_exit, we don't
	 * need to loop here.
	 */
	bus_teardown_intr(brdev, sc->irq_res, sc->intrhand);
	mtx_lock(&sc->mtx);
	sc->flags |= CBB_KTHREAD_DONE;
	while (sc->flags & CBB_KTHREAD_RUNNING) {
		DEVPRINTF((sc->dev, "Waiting for thread to die\n"));
		wakeup(&sc->intrhand);
		msleep(sc->event_thread, &sc->mtx, PWAIT, "cbbun", 0);
	}
	mtx_unlock(&sc->mtx);

	bus_release_resource(brdev, SYS_RES_IRQ, 0, sc->irq_res);
	bus_release_resource(brdev, SYS_RES_MEMORY, CBBR_SOCKBASE,
	    sc->base_res);
	mtx_destroy(&sc->mtx);
	return (0);
}