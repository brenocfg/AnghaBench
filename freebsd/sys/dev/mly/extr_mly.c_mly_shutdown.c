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
struct mly_softc {int mly_state; int /*<<< orphan*/  mly_timeout; int /*<<< orphan*/  mly_periodic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MLY_LOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_MASK_INTERRUPTS (struct mly_softc*) ; 
 int MLY_STATE_OPEN ; 
 int /*<<< orphan*/  MLY_UNLOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct mly_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ mly_flush (struct mly_softc*) ; 
 int /*<<< orphan*/  mly_printf (struct mly_softc*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
mly_shutdown(device_t dev)
{
    struct mly_softc	*sc = device_get_softc(dev);

    debug_called(1);

    MLY_LOCK(sc);
    if (sc->mly_state & MLY_STATE_OPEN) {
	MLY_UNLOCK(sc);
	return(EBUSY);
    }

    /* kill the periodic event */
    callout_stop(&sc->mly_periodic);
#ifdef MLY_DEBUG
    callout_stop(&sc->mly_timeout);
#endif

    /* flush controller */
    mly_printf(sc, "flushing cache...");
    printf("%s\n", mly_flush(sc) ? "failed" : "done");

    MLY_MASK_INTERRUPTS(sc);
    MLY_UNLOCK(sc);

    return(0);
}