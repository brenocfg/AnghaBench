#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u_int ;
struct scsi_vpd_device_id {scalar_t__ desc_list; } ;
struct TYPE_9__ {int /*<<< orphan*/  id_len; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_4__ devid_pat; int /*<<< orphan*/  inq_pat; } ;
struct device_match_pattern {int flags; scalar_t__ path_id; scalar_t__ target_id; scalar_t__ target_lun; TYPE_5__ data; } ;
struct TYPE_6__ {struct device_match_pattern device_pattern; } ;
struct dev_match_pattern {scalar_t__ type; TYPE_1__ pattern; } ;
struct cam_ed {scalar_t__ lun_id; scalar_t__ device_id_len; scalar_t__ device_id; int /*<<< orphan*/  inq_data; TYPE_3__* target; } ;
typedef  int dev_match_ret ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_8__ {scalar_t__ target_id; TYPE_2__* bus; } ;
struct TYPE_7__ {scalar_t__ path_id; } ;

/* Variables and functions */
 int DEV_MATCH_ANY ; 
 scalar_t__ DEV_MATCH_DEVICE ; 
 int DEV_MATCH_DEVID ; 
 int DEV_MATCH_INQUIRY ; 
 int DEV_MATCH_LUN ; 
 int DEV_MATCH_NONE ; 
 int DEV_MATCH_PATH ; 
 scalar_t__ DEV_MATCH_PERIPH ; 
 int DEV_MATCH_TARGET ; 
 int DM_RET_ACTION_MASK ; 
 int DM_RET_COPY ; 
 int DM_RET_DESCEND ; 
 int DM_RET_ERROR ; 
 int DM_RET_NONE ; 
 int DM_RET_STOP ; 
 scalar_t__ SVPD_DEVICE_ID_HDR_LEN ; 
 int /*<<< orphan*/ * cam_quirkmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_devid_match (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_static_inquiry_match ; 

__attribute__((used)) static dev_match_ret
xptdevicematch(struct dev_match_pattern *patterns, u_int num_patterns,
	       struct cam_ed *device)
{
	dev_match_ret retval;
	u_int i;

	retval = DM_RET_NONE;

	/*
	 * If we aren't given something to match against, that's an error.
	 */
	if (device == NULL)
		return(DM_RET_ERROR);

	/*
	 * If there are no match entries, then this device matches no
	 * matter what.
	 */
	if ((patterns == NULL) || (num_patterns == 0))
		return(DM_RET_DESCEND | DM_RET_COPY);

	for (i = 0; i < num_patterns; i++) {
		struct device_match_pattern *cur_pattern;
		struct scsi_vpd_device_id *device_id_page;

		/*
		 * If the pattern in question isn't for a device node, we
		 * aren't interested.
		 */
		if (patterns[i].type != DEV_MATCH_DEVICE) {
			if ((patterns[i].type == DEV_MATCH_PERIPH)
			 && ((retval & DM_RET_ACTION_MASK) == DM_RET_NONE))
				retval |= DM_RET_DESCEND;
			continue;
		}

		cur_pattern = &patterns[i].pattern.device_pattern;

		/* Error out if mutually exclusive options are specified. */
		if ((cur_pattern->flags & (DEV_MATCH_INQUIRY|DEV_MATCH_DEVID))
		 == (DEV_MATCH_INQUIRY|DEV_MATCH_DEVID))
			return(DM_RET_ERROR);

		/*
		 * If they want to match any device node, we give them any
		 * device node.
		 */
		if (cur_pattern->flags == DEV_MATCH_ANY)
			goto copy_dev_node;

		/*
		 * Not sure why someone would do this...
		 */
		if (cur_pattern->flags == DEV_MATCH_NONE)
			continue;

		if (((cur_pattern->flags & DEV_MATCH_PATH) != 0)
		 && (cur_pattern->path_id != device->target->bus->path_id))
			continue;

		if (((cur_pattern->flags & DEV_MATCH_TARGET) != 0)
		 && (cur_pattern->target_id != device->target->target_id))
			continue;

		if (((cur_pattern->flags & DEV_MATCH_LUN) != 0)
		 && (cur_pattern->target_lun != device->lun_id))
			continue;

		if (((cur_pattern->flags & DEV_MATCH_INQUIRY) != 0)
		 && (cam_quirkmatch((caddr_t)&device->inq_data,
				    (caddr_t)&cur_pattern->data.inq_pat,
				    1, sizeof(cur_pattern->data.inq_pat),
				    scsi_static_inquiry_match) == NULL))
			continue;

		device_id_page = (struct scsi_vpd_device_id *)device->device_id;
		if (((cur_pattern->flags & DEV_MATCH_DEVID) != 0)
		 && (device->device_id_len < SVPD_DEVICE_ID_HDR_LEN
		  || scsi_devid_match((uint8_t *)device_id_page->desc_list,
				      device->device_id_len
				    - SVPD_DEVICE_ID_HDR_LEN,
				      cur_pattern->data.devid_pat.id,
				      cur_pattern->data.devid_pat.id_len) != 0))
			continue;

copy_dev_node:
		/*
		 * If we get to this point, the user definitely wants
		 * information on this device.  So tell the caller to copy
		 * the data out.
		 */
		retval |= DM_RET_COPY;

		/*
		 * If the return action has been set to descend, then we
		 * know that we've already seen a peripheral matching
		 * expression, therefore we need to further descend the tree.
		 * This won't change by continuing around the loop, so we
		 * go ahead and return.  If we haven't seen a peripheral
		 * matching expression, we keep going around the loop until
		 * we exhaust the matching expressions.  We'll set the stop
		 * flag once we fall out of the loop.
		 */
		if ((retval & DM_RET_ACTION_MASK) == DM_RET_DESCEND)
			return(retval);
	}

	/*
	 * If the return action hasn't been set to descend yet, that means
	 * we haven't seen any peripheral matching patterns.  So tell the
	 * caller to stop descending the tree -- the user doesn't want to
	 * match against lower level tree elements.
	 */
	if ((retval & DM_RET_ACTION_MASK) == DM_RET_NONE)
		retval |= DM_RET_STOP;

	return(retval);
}