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
struct ciss_softc {int ciss_flags; int /*<<< orphan*/  ciss_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CISS_FLAG_CONTROL_OPEN ; 
 int EBUSY ; 
 int /*<<< orphan*/  ciss_flush_adapter (struct ciss_softc*) ; 
 int /*<<< orphan*/  ciss_free (struct ciss_softc*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct ciss_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ciss_detach(device_t dev)
{
    struct ciss_softc	*sc = device_get_softc(dev);

    debug_called(1);

    mtx_lock(&sc->ciss_mtx);
    if (sc->ciss_flags & CISS_FLAG_CONTROL_OPEN) {
	mtx_unlock(&sc->ciss_mtx);
	return (EBUSY);
    }

    /* flush adapter cache */
    ciss_flush_adapter(sc);

    /* release all resources.  The mutex is released and freed here too. */
    ciss_free(sc);

    return(0);
}