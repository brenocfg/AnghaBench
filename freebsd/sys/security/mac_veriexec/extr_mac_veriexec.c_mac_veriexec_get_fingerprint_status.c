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
struct vnode {int /*<<< orphan*/  v_tag; int /*<<< orphan*/  v_label; } ;
typedef  int fingerprint_status_t ;

/* Variables and functions */
#define  FINGERPRINT_FILE 130 
#define  FINGERPRINT_INDIRECT 129 
#define  FINGERPRINT_VALID 128 
 struct vnode* NULLVPTOLOWERVP (struct vnode*) ; 
 int SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

fingerprint_status_t
mac_veriexec_get_fingerprint_status(struct vnode *vp)
{
	fingerprint_status_t fps;

	fps = SLOT(vp->v_label);
	switch (fps) {
	case FINGERPRINT_VALID:
	case FINGERPRINT_INDIRECT:
	case FINGERPRINT_FILE:
		break;
	default:
		/* we may need to recurse */
		if (strcmp(vp->v_tag, "null") == 0) {
			struct vnode *ldvp;

			ldvp = NULLVPTOLOWERVP(vp);
			return mac_veriexec_get_fingerprint_status(ldvp);
		}
		break;
	}
	return fps;
}