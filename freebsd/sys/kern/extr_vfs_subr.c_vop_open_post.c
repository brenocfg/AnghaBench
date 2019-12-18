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
struct vop_open_args {int /*<<< orphan*/  a_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTE_OPEN ; 
 int /*<<< orphan*/  VFS_KNOTE_LOCKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vop_open_post(void *ap, int rc)
{
	struct vop_open_args *a = ap;

	if (!rc)
		VFS_KNOTE_LOCKED(a->a_vp, NOTE_OPEN);
}