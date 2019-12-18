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
struct vnode {int dummy; } ;
struct thread {int dummy; } ;
struct image_params {int /*<<< orphan*/  interpreted; int /*<<< orphan*/  attr; struct vnode* vp; } ;
typedef  int fingerprint_status_t ;
struct TYPE_2__ {int pr_securelevel; } ;

/* Variables and functions */
 int EAUTH ; 
 int EPERM ; 
#define  FINGERPRINT_FILE 134 
#define  FINGERPRINT_INDIRECT 133 
#define  FINGERPRINT_INVALID 132 
#define  FINGERPRINT_NODEV 131 
#define  FINGERPRINT_NOENTRY 130 
#define  FINGERPRINT_NOMATCH 129 
#define  FINGERPRINT_VALID 128 
 int /*<<< orphan*/  VERIEXEC_DEBUG (int,char*) ; 
 int /*<<< orphan*/  VERIEXEC_STATE_ACTIVE ; 
 int /*<<< orphan*/  VERIEXEC_STATE_ENFORCE ; 
 int /*<<< orphan*/  identify_error (struct image_params*,struct thread*,char*) ; 
 int mac_veriexec_get_fingerprint_status (struct vnode*) ; 
 scalar_t__ mac_veriexec_in_state (int /*<<< orphan*/ ) ; 
 int mac_veriexec_metadata_fetch_fingerprint_status (struct vnode*,int /*<<< orphan*/ ,struct thread*,int) ; 
 TYPE_1__ prison0 ; 

int
mac_veriexec_fingerprint_check_image(struct image_params *imgp,
    int check_files, struct thread *td)
{
	struct vnode *vp = imgp->vp;
	int error;
	fingerprint_status_t status;

	if (!mac_veriexec_in_state(VERIEXEC_STATE_ACTIVE))
		return 0;

	error = mac_veriexec_metadata_fetch_fingerprint_status(vp, imgp->attr,
	    td, check_files);
	if (error && error != EAUTH)
		return (error);

	/*
	 * By now status is set.
	 */
	status = mac_veriexec_get_fingerprint_status(vp);
	switch (status) {
	case FINGERPRINT_INVALID: /* should not happen */
		identify_error(imgp, td, "got unexpected FINGERPRINT_INVALID");
		error = EPERM;
		break;

	case FINGERPRINT_FILE:
		if (!check_files) {
			if (prison0.pr_securelevel > 1 ||
			    mac_veriexec_in_state(VERIEXEC_STATE_ENFORCE))
				error = EPERM;
		}
		break;

	case FINGERPRINT_VALID: /* is ok - report so if debug is on */
		VERIEXEC_DEBUG(4, ("Fingerprint matches\n"));
		break;

	case FINGERPRINT_INDIRECT: /* fingerprint ok but need to check
				      for direct execution */
		if (!imgp->interpreted) {
			identify_error(imgp, td, "attempted direct execution");
			if (prison0.pr_securelevel > 1 ||
			    mac_veriexec_in_state(VERIEXEC_STATE_ENFORCE))
				error = EPERM;
		}
		break;

	case FINGERPRINT_NOMATCH: /* does not match - whine about it */
		identify_error(imgp, td,
		    "fingerprint does not match loaded value");
		if (prison0.pr_securelevel > 1 ||
		    mac_veriexec_in_state(VERIEXEC_STATE_ENFORCE))
			error = EAUTH;
		break;

	case FINGERPRINT_NOENTRY: /* no entry in the list, complain */
		identify_error(imgp, td, "no fingerprint");
		if (prison0.pr_securelevel > 1 ||
		    mac_veriexec_in_state(VERIEXEC_STATE_ENFORCE))
			error = EAUTH;
		break;

	case FINGERPRINT_NODEV: /* no signatures for the device, complain */
		identify_error(imgp, td, "no signatures for device");
		if (prison0.pr_securelevel > 1 ||
		    mac_veriexec_in_state(VERIEXEC_STATE_ENFORCE))
			error = EAUTH;
		break;

	default: /* this should never happen. */
		identify_error(imgp, td, "invalid status field for vnode");
		error = EPERM;
	}
	return error; 
}