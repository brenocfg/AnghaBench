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
struct mtx {int dummy; } ;
struct enc_softc {int open_count; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 struct mtx* cam_periph_mtx (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 

__attribute__((used)) static void
enc_devgonecb(void *arg)
{
	struct cam_periph *periph;
	struct enc_softc  *enc;
	struct mtx *mtx;
	int i;

	periph = (struct cam_periph *)arg;
	mtx = cam_periph_mtx(periph);
	mtx_lock(mtx);
	enc = (struct enc_softc *)periph->softc;

	/*
	 * When we get this callback, we will get no more close calls from
	 * devfs.  So if we have any dangling opens, we need to release the
	 * reference held for that particular context.
	 */
	for (i = 0; i < enc->open_count; i++)
		cam_periph_release_locked(periph);

	enc->open_count = 0;

	/*
	 * Release the reference held for the device node, it is gone now.
	 */
	cam_periph_release_locked(periph);

	/*
	 * We reference the lock directly here, instead of using
	 * cam_periph_unlock().  The reason is that the final call to
	 * cam_periph_release_locked() above could result in the periph
	 * getting freed.  If that is the case, dereferencing the periph
	 * with a cam_periph_unlock() call would cause a page fault.
	 */
	mtx_unlock(mtx);
}