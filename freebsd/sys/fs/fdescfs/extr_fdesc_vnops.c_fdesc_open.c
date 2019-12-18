#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vop_open_args {TYPE_1__* a_td; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct TYPE_4__ {scalar_t__ fd_type; int /*<<< orphan*/  fd_fd; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_dupfd; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ Froot ; 
 TYPE_2__* VTOFDESC (struct vnode*) ; 

__attribute__((used)) static int
fdesc_open(struct vop_open_args *ap)
{
	struct vnode *vp = ap->a_vp;

	if (VTOFDESC(vp)->fd_type == Froot)
		return (0);

	/*
	 * XXX Kludge: set td->td_proc->p_dupfd to contain the value of the file
	 * descriptor being sought for duplication. The error return ensures
	 * that the vnode for this device will be released by vn_open. Open
	 * will detect this special error and take the actions in dupfdopen.
	 * Other callers of vn_open or VOP_OPEN will simply report the
	 * error.
	 */
	ap->a_td->td_dupfd = VTOFDESC(vp)->fd_fd;	/* XXX */
	return (ENODEV);
}