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
struct vop_remove_args {int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_dvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTE_DELETE ; 
 int /*<<< orphan*/  NOTE_WRITE ; 
 int /*<<< orphan*/  VFS_KNOTE_LOCKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vop_remove_post(void *ap, int rc)
{
	struct vop_remove_args *a = ap;

	if (!rc) {
		VFS_KNOTE_LOCKED(a->a_dvp, NOTE_WRITE);
		VFS_KNOTE_LOCKED(a->a_vp, NOTE_DELETE);
	}
}