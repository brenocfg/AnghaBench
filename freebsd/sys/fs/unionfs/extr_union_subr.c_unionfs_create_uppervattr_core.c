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
struct vattr {int va_mode; int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_type; int /*<<< orphan*/  va_ctime; int /*<<< orphan*/  va_mtime; int /*<<< orphan*/  va_atime; } ;
struct unionfs_mount {int um_copymode; int um_udir; int um_ufile; int /*<<< orphan*/  um_gid; int /*<<< orphan*/  um_uid; } ;
struct thread {TYPE_2__* td_proc; } ;
struct TYPE_4__ {TYPE_1__* p_fd; } ;
struct TYPE_3__ {int fd_cmask; } ;

/* Variables and functions */
#define  UNIONFS_MASQUERADE 129 
#define  UNIONFS_TRANSPARENT 128 
 int /*<<< orphan*/  VATTR_NULL (struct vattr*) ; 
 int /*<<< orphan*/  VDIR ; 

void
unionfs_create_uppervattr_core(struct unionfs_mount *ump,
			       struct vattr *lva,
			       struct vattr *uva,
			       struct thread *td)
{
	VATTR_NULL(uva);
	uva->va_type = lva->va_type;
	uva->va_atime = lva->va_atime;
	uva->va_mtime = lva->va_mtime;
	uva->va_ctime = lva->va_ctime;

	switch (ump->um_copymode) {
	case UNIONFS_TRANSPARENT:
		uva->va_mode = lva->va_mode;
		uva->va_uid = lva->va_uid;
		uva->va_gid = lva->va_gid;
		break;
	case UNIONFS_MASQUERADE:
		if (ump->um_uid == lva->va_uid) {
			uva->va_mode = lva->va_mode & 077077;
			uva->va_mode |= (lva->va_type == VDIR ? ump->um_udir : ump->um_ufile) & 0700;
			uva->va_uid = lva->va_uid;
			uva->va_gid = lva->va_gid;
		} else {
			uva->va_mode = (lva->va_type == VDIR ? ump->um_udir : ump->um_ufile);
			uva->va_uid = ump->um_uid;
			uva->va_gid = ump->um_gid;
		}
		break;
	default:		/* UNIONFS_TRADITIONAL */
		uva->va_mode = 0777 & ~td->td_proc->p_fd->fd_cmask;
		uva->va_uid = ump->um_uid;
		uva->va_gid = ump->um_gid;
		break;
	}
}