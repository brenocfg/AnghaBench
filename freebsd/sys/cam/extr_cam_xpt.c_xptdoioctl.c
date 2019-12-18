#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* periph_name; int index; int /*<<< orphan*/  unit_number; void* status; int /*<<< orphan*/  generation; } ;
struct TYPE_14__ {int /*<<< orphan*/  priority; } ;
struct TYPE_15__ {int flags; void* status; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  path_id; int /*<<< orphan*/  func_code; struct cam_path* path; TYPE_6__ pinfo; } ;
struct TYPE_13__ {int /*<<< orphan*/ * bio; } ;
union ccb {TYPE_4__ cgdl; TYPE_7__ ccb_h; TYPE_5__ csio; } ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct thread {int dummy; } ;
struct periph_driver {int /*<<< orphan*/  units; int /*<<< orphan*/  driver_name; } ;
struct cdev {int dummy; } ;
struct cam_periph_map_info {int dummy; } ;
struct cam_periph {TYPE_3__* path; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  periph_name; } ;
struct cam_path {int dummy; } ;
struct cam_ed {int /*<<< orphan*/  lun_id; int /*<<< orphan*/  generation; int /*<<< orphan*/  periphs; } ;
struct cam_eb {int dummy; } ;
typedef  int /*<<< orphan*/  mapinfo ;
typedef  scalar_t__ caddr_t ;
struct TYPE_16__ {struct cam_path* path; } ;
struct TYPE_11__ {struct cam_ed* device; TYPE_2__* target; TYPE_1__* bus; } ;
struct TYPE_10__ {int /*<<< orphan*/  target_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  path_id; } ;

/* Variables and functions */
#define  CAMGETPASSTHRU 137 
#define  CAMIOCOMMAND 136 
 int CAM_DATA_MASK ; 
 int CAM_DATA_VADDR ; 
 void* CAM_GDEVLIST_ERROR ; 
 void* CAM_GDEVLIST_LAST_DEVICE ; 
 void* CAM_GDEVLIST_MORE_DEVS ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int CAM_UNLOCKED ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOTSUP ; 
 int ENOTTY ; 
 int /*<<< orphan*/  MAXPHYS ; 
 struct cam_periph* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct cam_periph* SLIST_NEXT (struct cam_periph*,int /*<<< orphan*/ ) ; 
 struct cam_periph* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct cam_periph* TAILQ_NEXT (struct cam_periph*,int /*<<< orphan*/ ) ; 
#define  XPT_DEBUG 135 
#define  XPT_DEV_MATCH 134 
#define  XPT_ENG_INQ 133 
#define  XPT_PATH_INQ 132 
#define  XPT_RESET_BUS 131 
#define  XPT_SCAN_BUS 130 
#define  XPT_SCAN_LUN 129 
#define  XPT_SCAN_TGT 128 
 int /*<<< orphan*/  XPT_SCSI_IO ; 
 int /*<<< orphan*/  bcopy (union ccb*,union ccb*,int) ; 
 int /*<<< orphan*/  bzero (struct cam_periph_map_info*,int) ; 
 int cam_periph_mapmem (union ccb*,struct cam_periph_map_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_runccb (union ccb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_periph_unmapmem (union ccb*,struct cam_periph_map_info*) ; 
 struct periph_driver** periph_drivers ; 
 int /*<<< orphan*/  periph_links ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unit_links ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 union ccb* xpt_alloc_ccb () ; 
 void* xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cam_eb* xpt_find_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_merge_ccb (union ccb*,union ccb*) ; 
 int /*<<< orphan*/  xpt_path_lock (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_unlock (struct cam_path*) ; 
 TYPE_8__* xpt_periph ; 
 int /*<<< orphan*/  xpt_release_bus (struct cam_eb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_7__*,struct cam_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 

__attribute__((used)) static int
xptdoioctl(struct cdev *dev, u_long cmd, caddr_t addr, int flag, struct thread *td)
{
	int error;

	error = 0;

	switch(cmd) {
	/*
	 * For the transport layer CAMIOCOMMAND ioctl, we really only want
	 * to accept CCB types that don't quite make sense to send through a
	 * passthrough driver. XPT_PATH_INQ is an exception to this, as stated
	 * in the CAM spec.
	 */
	case CAMIOCOMMAND: {
		union ccb *ccb;
		union ccb *inccb;
		struct cam_eb *bus;

		inccb = (union ccb *)addr;
#if defined(BUF_TRACKING) || defined(FULL_BUF_TRACKING)
		if (inccb->ccb_h.func_code == XPT_SCSI_IO)
			inccb->csio.bio = NULL;
#endif

		if (inccb->ccb_h.flags & CAM_UNLOCKED)
			return (EINVAL);

		bus = xpt_find_bus(inccb->ccb_h.path_id);
		if (bus == NULL)
			return (EINVAL);

		switch (inccb->ccb_h.func_code) {
		case XPT_SCAN_BUS:
		case XPT_RESET_BUS:
			if (inccb->ccb_h.target_id != CAM_TARGET_WILDCARD ||
			    inccb->ccb_h.target_lun != CAM_LUN_WILDCARD) {
				xpt_release_bus(bus);
				return (EINVAL);
			}
			break;
		case XPT_SCAN_TGT:
			if (inccb->ccb_h.target_id == CAM_TARGET_WILDCARD ||
			    inccb->ccb_h.target_lun != CAM_LUN_WILDCARD) {
				xpt_release_bus(bus);
				return (EINVAL);
			}
			break;
		default:
			break;
		}

		switch(inccb->ccb_h.func_code) {
		case XPT_SCAN_BUS:
		case XPT_RESET_BUS:
		case XPT_PATH_INQ:
		case XPT_ENG_INQ:
		case XPT_SCAN_LUN:
		case XPT_SCAN_TGT:

			ccb = xpt_alloc_ccb();

			/*
			 * Create a path using the bus, target, and lun the
			 * user passed in.
			 */
			if (xpt_create_path(&ccb->ccb_h.path, NULL,
					    inccb->ccb_h.path_id,
					    inccb->ccb_h.target_id,
					    inccb->ccb_h.target_lun) !=
					    CAM_REQ_CMP){
				error = EINVAL;
				xpt_free_ccb(ccb);
				break;
			}
			/* Ensure all of our fields are correct */
			xpt_setup_ccb(&ccb->ccb_h, ccb->ccb_h.path,
				      inccb->ccb_h.pinfo.priority);
			xpt_merge_ccb(ccb, inccb);
			xpt_path_lock(ccb->ccb_h.path);
			cam_periph_runccb(ccb, NULL, 0, 0, NULL);
			xpt_path_unlock(ccb->ccb_h.path);
			bcopy(ccb, inccb, sizeof(union ccb));
			xpt_free_path(ccb->ccb_h.path);
			xpt_free_ccb(ccb);
			break;

		case XPT_DEBUG: {
			union ccb ccb;

			/*
			 * This is an immediate CCB, so it's okay to
			 * allocate it on the stack.
			 */

			/*
			 * Create a path using the bus, target, and lun the
			 * user passed in.
			 */
			if (xpt_create_path(&ccb.ccb_h.path, NULL,
					    inccb->ccb_h.path_id,
					    inccb->ccb_h.target_id,
					    inccb->ccb_h.target_lun) !=
					    CAM_REQ_CMP){
				error = EINVAL;
				break;
			}
			/* Ensure all of our fields are correct */
			xpt_setup_ccb(&ccb.ccb_h, ccb.ccb_h.path,
				      inccb->ccb_h.pinfo.priority);
			xpt_merge_ccb(&ccb, inccb);
			xpt_action(&ccb);
			bcopy(&ccb, inccb, sizeof(union ccb));
			xpt_free_path(ccb.ccb_h.path);
			break;

		}
		case XPT_DEV_MATCH: {
			struct cam_periph_map_info mapinfo;
			struct cam_path *old_path;

			/*
			 * We can't deal with physical addresses for this
			 * type of transaction.
			 */
			if ((inccb->ccb_h.flags & CAM_DATA_MASK) !=
			    CAM_DATA_VADDR) {
				error = EINVAL;
				break;
			}

			/*
			 * Save this in case the caller had it set to
			 * something in particular.
			 */
			old_path = inccb->ccb_h.path;

			/*
			 * We really don't need a path for the matching
			 * code.  The path is needed because of the
			 * debugging statements in xpt_action().  They
			 * assume that the CCB has a valid path.
			 */
			inccb->ccb_h.path = xpt_periph->path;

			bzero(&mapinfo, sizeof(mapinfo));

			/*
			 * Map the pattern and match buffers into kernel
			 * virtual address space.
			 */
			error = cam_periph_mapmem(inccb, &mapinfo, MAXPHYS);

			if (error) {
				inccb->ccb_h.path = old_path;
				break;
			}

			/*
			 * This is an immediate CCB, we can send it on directly.
			 */
			xpt_action(inccb);

			/*
			 * Map the buffers back into user space.
			 */
			cam_periph_unmapmem(inccb, &mapinfo);

			inccb->ccb_h.path = old_path;

			error = 0;
			break;
		}
		default:
			error = ENOTSUP;
			break;
		}
		xpt_release_bus(bus);
		break;
	}
	/*
	 * This is the getpassthru ioctl. It takes a XPT_GDEVLIST ccb as input,
	 * with the periphal driver name and unit name filled in.  The other
	 * fields don't really matter as input.  The passthrough driver name
	 * ("pass"), and unit number are passed back in the ccb.  The current
	 * device generation number, and the index into the device peripheral
	 * driver list, and the status are also passed back.  Note that
	 * since we do everything in one pass, unlike the XPT_GDEVLIST ccb,
	 * we never return a status of CAM_GDEVLIST_LIST_CHANGED.  It is
	 * (or rather should be) impossible for the device peripheral driver
	 * list to change since we look at the whole thing in one pass, and
	 * we do it with lock protection.
	 *
	 */
	case CAMGETPASSTHRU: {
		union ccb *ccb;
		struct cam_periph *periph;
		struct periph_driver **p_drv;
		char   *name;
		u_int unit;
		int base_periph_found;

		ccb = (union ccb *)addr;
		unit = ccb->cgdl.unit_number;
		name = ccb->cgdl.periph_name;
		base_periph_found = 0;
#if defined(BUF_TRACKING) || defined(FULL_BUF_TRACKING)
		if (ccb->ccb_h.func_code == XPT_SCSI_IO)
			ccb->csio.bio = NULL;
#endif

		/*
		 * Sanity check -- make sure we don't get a null peripheral
		 * driver name.
		 */
		if (*ccb->cgdl.periph_name == '\0') {
			error = EINVAL;
			break;
		}

		/* Keep the list from changing while we traverse it */
		xpt_lock_buses();

		/* first find our driver in the list of drivers */
		for (p_drv = periph_drivers; *p_drv != NULL; p_drv++)
			if (strcmp((*p_drv)->driver_name, name) == 0)
				break;

		if (*p_drv == NULL) {
			xpt_unlock_buses();
			ccb->ccb_h.status = CAM_REQ_CMP_ERR;
			ccb->cgdl.status = CAM_GDEVLIST_ERROR;
			*ccb->cgdl.periph_name = '\0';
			ccb->cgdl.unit_number = 0;
			error = ENOENT;
			break;
		}

		/*
		 * Run through every peripheral instance of this driver
		 * and check to see whether it matches the unit passed
		 * in by the user.  If it does, get out of the loops and
		 * find the passthrough driver associated with that
		 * peripheral driver.
		 */
		for (periph = TAILQ_FIRST(&(*p_drv)->units); periph != NULL;
		     periph = TAILQ_NEXT(periph, unit_links)) {

			if (periph->unit_number == unit)
				break;
		}
		/*
		 * If we found the peripheral driver that the user passed
		 * in, go through all of the peripheral drivers for that
		 * particular device and look for a passthrough driver.
		 */
		if (periph != NULL) {
			struct cam_ed *device;
			int i;

			base_periph_found = 1;
			device = periph->path->device;
			for (i = 0, periph = SLIST_FIRST(&device->periphs);
			     periph != NULL;
			     periph = SLIST_NEXT(periph, periph_links), i++) {
				/*
				 * Check to see whether we have a
				 * passthrough device or not.
				 */
				if (strcmp(periph->periph_name, "pass") == 0) {
					/*
					 * Fill in the getdevlist fields.
					 */
					strlcpy(ccb->cgdl.periph_name,
					       periph->periph_name,
					       sizeof(ccb->cgdl.periph_name));
					ccb->cgdl.unit_number =
						periph->unit_number;
					if (SLIST_NEXT(periph, periph_links))
						ccb->cgdl.status =
							CAM_GDEVLIST_MORE_DEVS;
					else
						ccb->cgdl.status =
						       CAM_GDEVLIST_LAST_DEVICE;
					ccb->cgdl.generation =
						device->generation;
					ccb->cgdl.index = i;
					/*
					 * Fill in some CCB header fields
					 * that the user may want.
					 */
					ccb->ccb_h.path_id =
						periph->path->bus->path_id;
					ccb->ccb_h.target_id =
						periph->path->target->target_id;
					ccb->ccb_h.target_lun =
						periph->path->device->lun_id;
					ccb->ccb_h.status = CAM_REQ_CMP;
					break;
				}
			}
		}

		/*
		 * If the periph is null here, one of two things has
		 * happened.  The first possibility is that we couldn't
		 * find the unit number of the particular peripheral driver
		 * that the user is asking about.  e.g. the user asks for
		 * the passthrough driver for "da11".  We find the list of
		 * "da" peripherals all right, but there is no unit 11.
		 * The other possibility is that we went through the list
		 * of peripheral drivers attached to the device structure,
		 * but didn't find one with the name "pass".  Either way,
		 * we return ENOENT, since we couldn't find something.
		 */
		if (periph == NULL) {
			ccb->ccb_h.status = CAM_REQ_CMP_ERR;
			ccb->cgdl.status = CAM_GDEVLIST_ERROR;
			*ccb->cgdl.periph_name = '\0';
			ccb->cgdl.unit_number = 0;
			error = ENOENT;
			/*
			 * It is unfortunate that this is even necessary,
			 * but there are many, many clueless users out there.
			 * If this is true, the user is looking for the
			 * passthrough driver, but doesn't have one in his
			 * kernel.
			 */
			if (base_periph_found == 1) {
				printf("xptioctl: pass driver is not in the "
				       "kernel\n");
				printf("xptioctl: put \"device pass\" in "
				       "your kernel config file\n");
			}
		}
		xpt_unlock_buses();
		break;
		}
	default:
		error = ENOTTY;
		break;
	}

	return(error);
}