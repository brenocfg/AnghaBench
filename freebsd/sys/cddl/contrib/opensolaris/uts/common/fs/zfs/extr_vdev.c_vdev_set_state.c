#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int vs_aux; } ;
struct TYPE_15__ {scalar_t__ vdev_state; int vdev_not_present; scalar_t__ vdev_prevstate; scalar_t__ vdev_parent; TYPE_2__* vdev_ops; void* vdev_removed; scalar_t__ vdev_checkremove; scalar_t__ vdev_forcefault; TYPE_1__ vdev_stat; int /*<<< orphan*/  vdev_delayed_close; TYPE_4__* vdev_spa; } ;
typedef  TYPE_3__ vdev_t ;
typedef  scalar_t__ vdev_state_t ;
typedef  int vdev_aux_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_16__ {TYPE_3__* spa_root_vdev; } ;
typedef  TYPE_4__ spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_14__ {scalar_t__ vdev_op_leaf; int /*<<< orphan*/  (* vdev_op_close ) (TYPE_3__*) ;} ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 char* FM_EREPORT_ZFS_DEVICE_BAD_GUID_SUM ; 
 char* FM_EREPORT_ZFS_DEVICE_BAD_LABEL ; 
 char* FM_EREPORT_ZFS_DEVICE_CORRUPT_DATA ; 
 char* FM_EREPORT_ZFS_DEVICE_NO_REPLICAS ; 
 char* FM_EREPORT_ZFS_DEVICE_OPEN_FAILED ; 
 char* FM_EREPORT_ZFS_DEVICE_TOO_SMALL ; 
 char* FM_EREPORT_ZFS_DEVICE_UNKNOWN ; 
 scalar_t__ SPA_LOAD_IMPORT ; 
 scalar_t__ SPA_LOAD_RECOVER ; 
#define  VDEV_AUX_BAD_GUID_SUM 133 
#define  VDEV_AUX_BAD_LABEL 132 
#define  VDEV_AUX_CORRUPT_DATA 131 
 int VDEV_AUX_NONE ; 
#define  VDEV_AUX_NO_REPLICAS 130 
#define  VDEV_AUX_OPEN_FAILED 129 
#define  VDEV_AUX_TOO_SMALL 128 
 scalar_t__ VDEV_STATE_CANT_OPEN ; 
 scalar_t__ VDEV_STATE_REMOVED ; 
 scalar_t__ spa_load_state (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 scalar_t__ vdev_is_dead (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_propagate_state (scalar_t__) ; 
 int /*<<< orphan*/  zfs_ereport_post (char const*,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_post_state_change (TYPE_4__*,TYPE_3__*) ; 

void
vdev_set_state(vdev_t *vd, boolean_t isopen, vdev_state_t state, vdev_aux_t aux)
{
	uint64_t save_state;
	spa_t *spa = vd->vdev_spa;

	if (state == vd->vdev_state) {
		vd->vdev_stat.vs_aux = aux;
		return;
	}

	save_state = vd->vdev_state;

	vd->vdev_state = state;
	vd->vdev_stat.vs_aux = aux;

	/*
	 * If we are setting the vdev state to anything but an open state, then
	 * always close the underlying device unless the device has requested
	 * a delayed close (i.e. we're about to remove or fault the device).
	 * Otherwise, we keep accessible but invalid devices open forever.
	 * We don't call vdev_close() itself, because that implies some extra
	 * checks (offline, etc) that we don't want here.  This is limited to
	 * leaf devices, because otherwise closing the device will affect other
	 * children.
	 */
	if (!vd->vdev_delayed_close && vdev_is_dead(vd) &&
	    vd->vdev_ops->vdev_op_leaf)
		vd->vdev_ops->vdev_op_close(vd);

	if (vd->vdev_removed &&
	    state == VDEV_STATE_CANT_OPEN &&
	    (aux == VDEV_AUX_OPEN_FAILED || vd->vdev_checkremove)) {
		/*
		 * If the previous state is set to VDEV_STATE_REMOVED, then this
		 * device was previously marked removed and someone attempted to
		 * reopen it.  If this failed due to a nonexistent device, then
		 * keep the device in the REMOVED state.  We also let this be if
		 * it is one of our special test online cases, which is only
		 * attempting to online the device and shouldn't generate an FMA
		 * fault.
		 */
		vd->vdev_state = VDEV_STATE_REMOVED;
		vd->vdev_stat.vs_aux = VDEV_AUX_NONE;
	} else if (state == VDEV_STATE_REMOVED) {
		vd->vdev_removed = B_TRUE;
	} else if (state == VDEV_STATE_CANT_OPEN) {
		/*
		 * If we fail to open a vdev during an import or recovery, we
		 * mark it as "not available", which signifies that it was
		 * never there to begin with.  Failure to open such a device
		 * is not considered an error.
		 */
		if ((spa_load_state(spa) == SPA_LOAD_IMPORT ||
		    spa_load_state(spa) == SPA_LOAD_RECOVER) &&
		    vd->vdev_ops->vdev_op_leaf)
			vd->vdev_not_present = 1;

		/*
		 * Post the appropriate ereport.  If the 'prevstate' field is
		 * set to something other than VDEV_STATE_UNKNOWN, it indicates
		 * that this is part of a vdev_reopen().  In this case, we don't
		 * want to post the ereport if the device was already in the
		 * CANT_OPEN state beforehand.
		 *
		 * If the 'checkremove' flag is set, then this is an attempt to
		 * online the device in response to an insertion event.  If we
		 * hit this case, then we have detected an insertion event for a
		 * faulted or offline device that wasn't in the removed state.
		 * In this scenario, we don't post an ereport because we are
		 * about to replace the device, or attempt an online with
		 * vdev_forcefault, which will generate the fault for us.
		 */
		if ((vd->vdev_prevstate != state || vd->vdev_forcefault) &&
		    !vd->vdev_not_present && !vd->vdev_checkremove &&
		    vd != spa->spa_root_vdev) {
			const char *class;

			switch (aux) {
			case VDEV_AUX_OPEN_FAILED:
				class = FM_EREPORT_ZFS_DEVICE_OPEN_FAILED;
				break;
			case VDEV_AUX_CORRUPT_DATA:
				class = FM_EREPORT_ZFS_DEVICE_CORRUPT_DATA;
				break;
			case VDEV_AUX_NO_REPLICAS:
				class = FM_EREPORT_ZFS_DEVICE_NO_REPLICAS;
				break;
			case VDEV_AUX_BAD_GUID_SUM:
				class = FM_EREPORT_ZFS_DEVICE_BAD_GUID_SUM;
				break;
			case VDEV_AUX_TOO_SMALL:
				class = FM_EREPORT_ZFS_DEVICE_TOO_SMALL;
				break;
			case VDEV_AUX_BAD_LABEL:
				class = FM_EREPORT_ZFS_DEVICE_BAD_LABEL;
				break;
			default:
				class = FM_EREPORT_ZFS_DEVICE_UNKNOWN;
			}

			zfs_ereport_post(class, spa, vd, NULL, save_state, 0);
		}

		/* Erase any notion of persistent removed state */
		vd->vdev_removed = B_FALSE;
	} else {
		vd->vdev_removed = B_FALSE;
	}

	/*
	* Notify the fmd of the state change.  Be verbose and post
	* notifications even for stuff that's not important; the fmd agent can
	* sort it out.  Don't emit state change events for non-leaf vdevs since
	* they can't change state on their own.  The FMD can check their state
	* if it wants to when it sees that a leaf vdev had a state change.
	*/
	if (vd->vdev_ops->vdev_op_leaf)
		zfs_post_state_change(spa, vd);

	if (!isopen && vd->vdev_parent)
		vdev_propagate_state(vd->vdev_parent);
}