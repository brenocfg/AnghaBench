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
struct nda_softc {int /*<<< orphan*/  flags; } ;
struct disk {scalar_t__ d_drv1; } ;
struct cam_periph {scalar_t__ softc; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int,char*) ; 
 int CAM_DEBUG_PERIPH ; 
 int CAM_DEBUG_TRACE ; 
 int ENXIO ; 
 int /*<<< orphan*/  NDA_FLAG_OPEN ; 
 int PCATCH ; 
 int PRIBIO ; 
 scalar_t__ cam_periph_acquire (struct cam_periph*) ; 
 int cam_periph_hold (struct cam_periph*,int) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unhold (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 

__attribute__((used)) static int
ndaopen(struct disk *dp)
{
	struct cam_periph *periph;
	struct nda_softc *softc;
	int error;

	periph = (struct cam_periph *)dp->d_drv1;
	if (cam_periph_acquire(periph) != 0) {
		return(ENXIO);
	}

	cam_periph_lock(periph);
	if ((error = cam_periph_hold(periph, PRIBIO|PCATCH)) != 0) {
		cam_periph_unlock(periph);
		cam_periph_release(periph);
		return (error);
	}

	CAM_DEBUG(periph->path, CAM_DEBUG_TRACE | CAM_DEBUG_PERIPH,
	    ("ndaopen\n"));

	softc = (struct nda_softc *)periph->softc;
	softc->flags |= NDA_FLAG_OPEN;

	cam_periph_unhold(periph);
	cam_periph_unlock(periph);
	return (0);
}