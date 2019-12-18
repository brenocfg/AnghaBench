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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct sg_softc {int flags; int /*<<< orphan*/  open_count; } ;
struct cdev {scalar_t__ si_drv1; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int SG_FLAG_INVALID ; 
 scalar_t__ cam_periph_acquire (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int securelevel_gt (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sgopen(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct cam_periph *periph;
	struct sg_softc *softc;
	int error = 0;

	periph = (struct cam_periph *)dev->si_drv1;
	if (cam_periph_acquire(periph) != 0)
		return (ENXIO);

	/*
	 * Don't allow access when we're running at a high securelevel.
	 */
	error = securelevel_gt(td->td_ucred, 1);
	if (error) {
		cam_periph_release(periph);
		return (error);
	}

	cam_periph_lock(periph);

	softc = (struct sg_softc *)periph->softc;
	if (softc->flags & SG_FLAG_INVALID) {
		cam_periph_release_locked(periph);
		cam_periph_unlock(periph);
		return (ENXIO);
	}

	softc->open_count++;

	cam_periph_unlock(periph);

	return (error);
}