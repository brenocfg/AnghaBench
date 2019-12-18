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
struct vnode {int /*<<< orphan*/  v_label; int /*<<< orphan*/  v_tag; } ;
typedef  int /*<<< orphan*/  fingerprint_status_t ;

/* Variables and functions */
 struct vnode* NULLVPTOLOWERVP (struct vnode*) ; 
 int /*<<< orphan*/  SLOT_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void
mac_veriexec_set_fingerprint_status(struct vnode *vp,
    fingerprint_status_t fp_status)
{

	/* recurse until we find the real storage */
	if (strcmp(vp->v_tag, "null") == 0) {
		struct vnode *ldvp;

		ldvp = NULLVPTOLOWERVP(vp);
		mac_veriexec_set_fingerprint_status(ldvp, fp_status);
		return;
	}
	SLOT_SET(vp->v_label, fp_status);
}