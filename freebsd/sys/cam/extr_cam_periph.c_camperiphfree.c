#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  func_code; } ;
union ccb {int /*<<< orphan*/  cpi; TYPE_1__ ccb_h; } ;
struct periph_driver {int /*<<< orphan*/  generation; int /*<<< orphan*/  units; int /*<<< orphan*/  driver_name; } ;
struct cam_periph {scalar_t__ periph_allocating; int flags; int deferred_ac; int /*<<< orphan*/  path; int /*<<< orphan*/  (* deferred_callback ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* periph_dtor ) (struct cam_periph*) ;int /*<<< orphan*/  periph_name; int /*<<< orphan*/  unit_number; } ;

/* Variables and functions */
#define  AC_FOUND_DEVICE 129 
#define  AC_PATH_REGISTERED 128 
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_INFO ; 
 int CAM_PERIPH_ANNOUNCED ; 
 int CAM_PERIPH_FREE ; 
 int CAM_PERIPH_NEW_DEV_FOUND ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_CAMPERIPH ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPT_GDEV_TYPE ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cam_periph*,int /*<<< orphan*/ ) ; 
 struct periph_driver** periph_drivers ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rebooting ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cam_periph*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  unit_links ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_path_inq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xpt_remove_periph (struct cam_periph*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 

__attribute__((used)) static void
camperiphfree(struct cam_periph *periph)
{
	struct periph_driver **p_drv;
	struct periph_driver *drv;

	cam_periph_assert(periph, MA_OWNED);
	KASSERT(periph->periph_allocating == 0, ("%s%d: freed while allocating",
	    periph->periph_name, periph->unit_number));
	for (p_drv = periph_drivers; *p_drv != NULL; p_drv++) {
		if (strcmp((*p_drv)->driver_name, periph->periph_name) == 0)
			break;
	}
	if (*p_drv == NULL) {
		printf("camperiphfree: attempt to free non-existant periph\n");
		return;
	}
	/*
	 * Cache a pointer to the periph_driver structure.  If a
	 * periph_driver is added or removed from the array (see
	 * periphdriver_register()) while we drop the toplogy lock
	 * below, p_drv may change.  This doesn't protect against this
	 * particular periph_driver going away.  That will require full
	 * reference counting in the periph_driver infrastructure.
	 */
	drv = *p_drv;

	/*
	 * We need to set this flag before dropping the topology lock, to
	 * let anyone who is traversing the list that this peripheral is
	 * about to be freed, and there will be no more reference count
	 * checks.
	 */
	periph->flags |= CAM_PERIPH_FREE;

	/*
	 * The peripheral destructor semantics dictate calling with only the
	 * SIM mutex held.  Since it might sleep, it should not be called
	 * with the topology lock held.
	 */
	xpt_unlock_buses();

	/*
	 * We need to call the peripheral destructor prior to removing the
	 * peripheral from the list.  Otherwise, we risk running into a
	 * scenario where the peripheral unit number may get reused
	 * (because it has been removed from the list), but some resources
	 * used by the peripheral are still hanging around.  In particular,
	 * the devfs nodes used by some peripherals like the pass(4) driver
	 * aren't fully cleaned up until the destructor is run.  If the
	 * unit number is reused before the devfs instance is fully gone,
	 * devfs will panic.
	 */
	if (periph->periph_dtor != NULL)
		periph->periph_dtor(periph);

	/*
	 * The peripheral list is protected by the topology lock.
	 */
	xpt_lock_buses();

	TAILQ_REMOVE(&drv->units, periph, unit_links);
	drv->generation++;

	xpt_remove_periph(periph);

	xpt_unlock_buses();
	if ((periph->flags & CAM_PERIPH_ANNOUNCED) && !rebooting)
		xpt_print(periph->path, "Periph destroyed\n");
	else
		CAM_DEBUG(periph->path, CAM_DEBUG_INFO, ("Periph destroyed\n"));

	if (periph->flags & CAM_PERIPH_NEW_DEV_FOUND) {
		union ccb ccb;
		void *arg;

		switch (periph->deferred_ac) {
		case AC_FOUND_DEVICE:
			ccb.ccb_h.func_code = XPT_GDEV_TYPE;
			xpt_setup_ccb(&ccb.ccb_h, periph->path, CAM_PRIORITY_NORMAL);
			xpt_action(&ccb);
			arg = &ccb;
			break;
		case AC_PATH_REGISTERED:
			xpt_path_inq(&ccb.cpi, periph->path);
			arg = &ccb;
			break;
		default:
			arg = NULL;
			break;
		}
		periph->deferred_callback(NULL, periph->deferred_ac,
					  periph->path, arg);
	}
	xpt_free_path(periph->path);
	free(periph, M_CAMPERIPH);
	xpt_lock_buses();
}