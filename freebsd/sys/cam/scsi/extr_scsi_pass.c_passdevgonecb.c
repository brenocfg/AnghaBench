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
struct pass_softc {int open_count; int /*<<< orphan*/  shutdown_kqueue_task; } ;
struct mtx {int dummy; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct mtx* cam_periph_mtx (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  passrejectios (struct cam_periph*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static void
passdevgonecb(void *arg)
{
	struct cam_periph *periph;
	struct mtx *mtx;
	struct pass_softc *softc;
	int i;

	periph = (struct cam_periph *)arg;
	mtx = cam_periph_mtx(periph);
	mtx_lock(mtx);

	softc = (struct pass_softc *)periph->softc;
	KASSERT(softc->open_count >= 0, ("Negative open count %d",
		softc->open_count));

	/*
	 * When we get this callback, we will get no more close calls from
	 * devfs.  So if we have any dangling opens, we need to release the
	 * reference held for that particular context.
	 */
	for (i = 0; i < softc->open_count; i++)
		cam_periph_release_locked(periph);

	softc->open_count = 0;

	/*
	 * Release the reference held for the device node, it is gone now.
	 * Accordingly, inform all queued I/Os of their fate.
	 */
	cam_periph_release_locked(periph);
	passrejectios(periph);

	/*
	 * We reference the SIM lock directly here, instead of using
	 * cam_periph_unlock().  The reason is that the final call to
	 * cam_periph_release_locked() above could result in the periph
	 * getting freed.  If that is the case, dereferencing the periph
	 * with a cam_periph_unlock() call would cause a page fault.
	 */
	mtx_unlock(mtx);

	/*
	 * We have to remove our kqueue context from a thread because it
	 * may sleep.  It would be nice if we could get a callback from
	 * kqueue when it is done cleaning up resources.
	 */
	taskqueue_enqueue(taskqueue_thread, &softc->shutdown_kqueue_task);
}