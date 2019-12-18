#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct vnode {TYPE_3__* v_mount; } ;
struct TYPE_13__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_22__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_20__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_18__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct vattr {scalar_t__ va_fsid; int va_type; scalar_t__ va_size; int va_bytes; int /*<<< orphan*/  va_gen; int /*<<< orphan*/  va_flags; int /*<<< orphan*/  va_blocksize; TYPE_11__ va_birthtime; TYPE_9__ va_ctime; TYPE_7__ va_mtime; TYPE_5__ va_atime; int /*<<< orphan*/  va_rdev; int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_nlink; int /*<<< orphan*/  va_mode; int /*<<< orphan*/  va_fileid; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_12__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_21__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_19__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_17__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct stat {scalar_t__ st_dev; scalar_t__ st_size; int st_blocks; int /*<<< orphan*/  st_gen; int /*<<< orphan*/  st_flags; int /*<<< orphan*/  st_blksize; TYPE_10__ st_birthtim; TYPE_8__ st_ctim; TYPE_6__ st_mtim; TYPE_4__ st_atim; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_ino; } ;
struct TYPE_14__ {scalar_t__* val; } ;
struct TYPE_15__ {TYPE_1__ f_fsid; } ;
struct TYPE_16__ {TYPE_2__ mnt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (struct vnode*) ; 
 int EBADF ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  NODEV ; 
 scalar_t__ OFF_MAX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PRIV_VFS_GENERATION ; 
 int S_BLKSIZE ; 
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFIFO ; 
 int /*<<< orphan*/  S_IFLNK ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  S_IFSOCK ; 
#define  VBLK 134 
#define  VCHR 133 
#define  VDIR 132 
#define  VFIFO 131 
#define  VLNK 130 
 scalar_t__ VNOVAL ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
#define  VREG 129 
#define  VSOCK 128 
 int /*<<< orphan*/  bzero (struct stat*,int) ; 
 int mac_vnode_check_stat (struct ucred*,struct ucred*,struct vnode*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ priv_check (struct thread*,int /*<<< orphan*/ ) ; 

int
vn_stat(struct vnode *vp, struct stat *sb, struct ucred *active_cred,
    struct ucred *file_cred, struct thread *td)
{
	struct vattr vattr;
	struct vattr *vap;
	int error;
	u_short mode;

	AUDIT_ARG_VNODE1(vp);
#ifdef MAC
	error = mac_vnode_check_stat(active_cred, file_cred, vp);
	if (error)
		return (error);
#endif

	vap = &vattr;

	/*
	 * Initialize defaults for new and unusual fields, so that file
	 * systems which don't support these fields don't need to know
	 * about them.
	 */
	vap->va_birthtime.tv_sec = -1;
	vap->va_birthtime.tv_nsec = 0;
	vap->va_fsid = VNOVAL;
	vap->va_rdev = NODEV;

	error = VOP_GETATTR(vp, vap, active_cred);
	if (error)
		return (error);

	/*
	 * Zero the spare stat fields
	 */
	bzero(sb, sizeof *sb);

	/*
	 * Copy from vattr table
	 */
	if (vap->va_fsid != VNOVAL)
		sb->st_dev = vap->va_fsid;
	else
		sb->st_dev = vp->v_mount->mnt_stat.f_fsid.val[0];
	sb->st_ino = vap->va_fileid;
	mode = vap->va_mode;
	switch (vap->va_type) {
	case VREG:
		mode |= S_IFREG;
		break;
	case VDIR:
		mode |= S_IFDIR;
		break;
	case VBLK:
		mode |= S_IFBLK;
		break;
	case VCHR:
		mode |= S_IFCHR;
		break;
	case VLNK:
		mode |= S_IFLNK;
		break;
	case VSOCK:
		mode |= S_IFSOCK;
		break;
	case VFIFO:
		mode |= S_IFIFO;
		break;
	default:
		return (EBADF);
	}
	sb->st_mode = mode;
	sb->st_nlink = vap->va_nlink;
	sb->st_uid = vap->va_uid;
	sb->st_gid = vap->va_gid;
	sb->st_rdev = vap->va_rdev;
	if (vap->va_size > OFF_MAX)
		return (EOVERFLOW);
	sb->st_size = vap->va_size;
	sb->st_atim.tv_sec = vap->va_atime.tv_sec;
	sb->st_atim.tv_nsec = vap->va_atime.tv_nsec;
	sb->st_mtim.tv_sec = vap->va_mtime.tv_sec;
	sb->st_mtim.tv_nsec = vap->va_mtime.tv_nsec;
	sb->st_ctim.tv_sec = vap->va_ctime.tv_sec;
	sb->st_ctim.tv_nsec = vap->va_ctime.tv_nsec;
	sb->st_birthtim.tv_sec = vap->va_birthtime.tv_sec;
	sb->st_birthtim.tv_nsec = vap->va_birthtime.tv_nsec;

        /*
	 * According to www.opengroup.org, the meaning of st_blksize is 
	 *   "a filesystem-specific preferred I/O block size for this 
	 *    object.  In some filesystem types, this may vary from file
	 *    to file"
	 * Use miminum/default of PAGE_SIZE (e.g. for VCHR).
	 */

	sb->st_blksize = max(PAGE_SIZE, vap->va_blocksize);
	
	sb->st_flags = vap->va_flags;
	if (priv_check(td, PRIV_VFS_GENERATION))
		sb->st_gen = 0;
	else
		sb->st_gen = vap->va_gen;

	sb->st_blocks = vap->va_bytes / S_BLKSIZE;
	return (0);
}