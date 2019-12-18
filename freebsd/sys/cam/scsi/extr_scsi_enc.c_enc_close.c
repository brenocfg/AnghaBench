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
struct thread {int dummy; } ;
struct mtx {int dummy; } ;
struct enc_softc {int /*<<< orphan*/  open_count; } ;
struct cdev {scalar_t__ si_drv1; } ;
struct cam_periph {struct enc_softc* softc; } ;

/* Variables and functions */
 struct mtx* cam_periph_mtx (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 

__attribute__((used)) static int
enc_close(struct cdev *dev, int flag, int fmt, struct thread *td)
{
	struct cam_periph *periph;
	struct enc_softc  *enc;
	struct mtx *mtx;

	periph = (struct cam_periph *)dev->si_drv1;
	mtx = cam_periph_mtx(periph);
	mtx_lock(mtx);

	enc = periph->softc;
	enc->open_count--;

	cam_periph_release_locked(periph);

	/*
	 * We reference the lock directly here, instead of using
	 * cam_periph_unlock().  The reason is that the call to
	 * cam_periph_release_locked() above could result in the periph
	 * getting freed.  If that is the case, dereferencing the periph
	 * with a cam_periph_unlock() call would cause a page fault.
	 *
	 * cam_periph_release() avoids this problem using the same method,
	 * but we're manually acquiring and dropping the lock here to
	 * protect the open count and avoid another lock acquisition and
	 * release.
	 */
	mtx_unlock(mtx);

	return (0);
}