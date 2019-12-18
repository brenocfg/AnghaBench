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
struct xbd_softc {int /*<<< orphan*/  xbd_io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  XBDF_GNT_SHORTAGE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xbd_startio (struct xbd_softc*) ; 
 int /*<<< orphan*/  xbd_thaw (struct xbd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xbd_restart_queue_callback(void *arg)
{
	struct xbd_softc *sc = arg;

	mtx_lock(&sc->xbd_io_lock);

	xbd_thaw(sc, XBDF_GNT_SHORTAGE);

	xbd_startio(sc);

	mtx_unlock(&sc->xbd_io_lock);
}