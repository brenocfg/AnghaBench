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
struct pt_softc {int /*<<< orphan*/  flags; } ;
struct cdev {scalar_t__ si_drv1; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_FLAG_OPEN ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 

__attribute__((used)) static int
ptclose(struct cdev *dev, int flag, int fmt, struct thread *td)
{
	struct	cam_periph *periph;
	struct	pt_softc *softc;

	periph = (struct cam_periph *)dev->si_drv1;
	softc = (struct pt_softc *)periph->softc;

	cam_periph_lock(periph);

	softc->flags &= ~PT_FLAG_OPEN;
	cam_periph_release_locked(periph);
	cam_periph_unlock(periph);
	return (0);
}