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
typedef  union ccb {int dummy; } ccb ;
struct sg_softc {int /*<<< orphan*/  device_stats; int /*<<< orphan*/  maxio; } ;
struct cam_periph_map_info {int dummy; } ;
struct cam_periph {struct sg_softc* softc; } ;
typedef  int /*<<< orphan*/  mapinfo ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
 int /*<<< orphan*/  SF_RETRY_UA ; 
 int /*<<< orphan*/  bzero (struct cam_periph_map_info*,int) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int cam_periph_mapmem (union ccb*,struct cam_periph_map_info*,int /*<<< orphan*/ ) ; 
 int cam_periph_runccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unmapmem (union ccb*,struct cam_periph_map_info*) ; 
 int /*<<< orphan*/  sgerror ; 

__attribute__((used)) static int
sgsendccb(struct cam_periph *periph, union ccb *ccb)
{
	struct sg_softc *softc;
	struct cam_periph_map_info mapinfo;
	int error;

	softc = periph->softc;
	bzero(&mapinfo, sizeof(mapinfo));

	/*
	 * cam_periph_mapmem calls into proc and vm functions that can
	 * sleep as well as trigger I/O, so we can't hold the lock.
	 * Dropping it here is reasonably safe.
	 * The only CCB opcode that is possible here is XPT_SCSI_IO, no
	 * need for additional checks.
	 */
	cam_periph_unlock(periph);
	error = cam_periph_mapmem(ccb, &mapinfo, softc->maxio);
	cam_periph_lock(periph);
	if (error)
		return (error);

	error = cam_periph_runccb(ccb,
				  sgerror,
				  CAM_RETRY_SELTO,
				  SF_RETRY_UA,
				  softc->device_stats);

	cam_periph_unlock(periph);
	cam_periph_unmapmem(ccb, &mapinfo);
	cam_periph_lock(periph);

	return (error);
}