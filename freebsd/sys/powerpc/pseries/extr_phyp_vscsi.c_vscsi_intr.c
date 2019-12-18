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
struct vscsi_softc {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vscsi_check_response_queue (struct vscsi_softc*) ; 

__attribute__((used)) static void
vscsi_intr(void *xsc)
{
	struct vscsi_softc *sc = xsc;

	mtx_lock(&sc->io_lock);
	vscsi_check_response_queue(sc);
	mtx_unlock(&sc->io_lock);
}