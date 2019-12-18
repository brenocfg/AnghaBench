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
struct ow_temp_softc {int flags; int /*<<< orphan*/  temp_lock; int /*<<< orphan*/  event_thread; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int OW_TEMP_DONE ; 
 int OW_TEMP_RUNNING ; 
 int /*<<< orphan*/  PWAIT ; 
 struct ow_temp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct ow_temp_softc*) ; 

__attribute__((used)) static int
ow_temp_detach(device_t dev)
{
	struct ow_temp_softc *sc;

	sc = device_get_softc(dev);

	/*
	 * Wait for the thread to die.  kproc_exit will do a wakeup
	 * on the event thread's struct thread * so that we know it is
	 * safe to proceed.  IF the thread is running, set the please
	 * die flag and wait for it to comply.  Since the wakeup on
	 * the event thread happens only in kproc_exit, we don't
	 * need to loop here.
	 */
	mtx_lock(&sc->temp_lock);
	sc->flags |= OW_TEMP_DONE;
	while (sc->flags & OW_TEMP_RUNNING) {
		wakeup(sc);
		msleep(sc->event_thread, &sc->temp_lock, PWAIT, "owtun", 0);
	}
	mtx_destroy(&sc->temp_lock);
	
	return 0;
}