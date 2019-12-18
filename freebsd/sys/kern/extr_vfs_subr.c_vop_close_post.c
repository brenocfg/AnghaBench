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
struct vop_close_args {scalar_t__ a_cred; int a_fflag; TYPE_1__* a_vp; } ;
struct TYPE_2__ {int v_iflag; } ;

/* Variables and functions */
 int FWRITE ; 
 scalar_t__ NOCRED ; 
 int /*<<< orphan*/  NOTE_CLOSE ; 
 int /*<<< orphan*/  NOTE_CLOSE_WRITE ; 
 int /*<<< orphan*/  VFS_KNOTE_LOCKED (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 

void
vop_close_post(void *ap, int rc)
{
	struct vop_close_args *a = ap;

	if (!rc && (a->a_cred != NOCRED || /* filter out revokes */
	    (a->a_vp->v_iflag & VI_DOOMED) == 0)) {
		VFS_KNOTE_LOCKED(a->a_vp, (a->a_fflag & FWRITE) != 0 ?
		    NOTE_CLOSE_WRITE : NOTE_CLOSE);
	}
}