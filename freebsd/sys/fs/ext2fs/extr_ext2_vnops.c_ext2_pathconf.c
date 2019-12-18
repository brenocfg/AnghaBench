#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vop_pathconf_args {int a_name; int* a_retval; TYPE_4__* a_vp; } ;
struct TYPE_8__ {TYPE_2__* v_mount; int /*<<< orphan*/  v_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_e2fs; } ;
struct TYPE_5__ {int f_iosize; int f_bsize; } ;
struct TYPE_6__ {int mnt_flag; TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int ACL_MAX_ENTRIES ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXT2F_ROCOMPAT_DIR_NLINK ; 
 int /*<<< orphan*/  EXT2_HAS_RO_COMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EXT4_LINK_MAX ; 
 int INT_MAX ; 
 int MAXPATHLEN ; 
 int MNT_ACLS ; 
 int NAME_MAX ; 
 int PAGE_SIZE ; 
 int PIPE_BUF ; 
 int /*<<< orphan*/  VDIR ; 
 int /*<<< orphan*/  VFIFO ; 
 TYPE_3__* VTOI (TYPE_4__*) ; 
#define  _PC_ACL_EXTENDED 144 
#define  _PC_ACL_PATH_MAX 143 
#define  _PC_ALLOC_SIZE_MIN 142 
#define  _PC_CHOWN_RESTRICTED 141 
#define  _PC_FILESIZEBITS 140 
#define  _PC_LINK_MAX 139 
#define  _PC_MIN_HOLE_SIZE 138 
#define  _PC_NAME_MAX 137 
#define  _PC_NO_TRUNC 136 
#define  _PC_PIPE_BUF 135 
#define  _PC_PRIO_IO 134 
#define  _PC_REC_INCR_XFER_SIZE 133 
#define  _PC_REC_MAX_XFER_SIZE 132 
#define  _PC_REC_MIN_XFER_SIZE 131 
#define  _PC_REC_XFER_ALIGN 130 
#define  _PC_SYMLINK_MAX 129 
#define  _PC_SYNC_IO 128 
 int vop_stdpathconf (struct vop_pathconf_args*) ; 

__attribute__((used)) static int
ext2_pathconf(struct vop_pathconf_args *ap)
{
	int error = 0;

	switch (ap->a_name) {
	case _PC_LINK_MAX:
		if (EXT2_HAS_RO_COMPAT_FEATURE(VTOI(ap->a_vp)->i_e2fs,
		    EXT2F_ROCOMPAT_DIR_NLINK))
			*ap->a_retval = INT_MAX;
		else
			*ap->a_retval = EXT4_LINK_MAX;
		break;
	case _PC_NAME_MAX:
		*ap->a_retval = NAME_MAX;
		break;
	case _PC_PIPE_BUF:
		if (ap->a_vp->v_type == VDIR || ap->a_vp->v_type == VFIFO)
			*ap->a_retval = PIPE_BUF;
		else
			error = EINVAL;
		break;
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 1;
		break;
	case _PC_NO_TRUNC:
		*ap->a_retval = 1;
		break;

#ifdef UFS_ACL
	case _PC_ACL_EXTENDED:
		if (ap->a_vp->v_mount->mnt_flag & MNT_ACLS)
			*ap->a_retval = 1;
		else
			*ap->a_retval = 0;
		break;
	case _PC_ACL_PATH_MAX:
		if (ap->a_vp->v_mount->mnt_flag & MNT_ACLS)
			*ap->a_retval = ACL_MAX_ENTRIES;
		else
			*ap->a_retval = 3;
		break;
#endif /* UFS_ACL */

	case _PC_MIN_HOLE_SIZE:
		*ap->a_retval = ap->a_vp->v_mount->mnt_stat.f_iosize;
		break;
	case _PC_PRIO_IO:
		*ap->a_retval = 0;
		break;
	case _PC_SYNC_IO:
		*ap->a_retval = 0;
		break;
	case _PC_ALLOC_SIZE_MIN:
		*ap->a_retval = ap->a_vp->v_mount->mnt_stat.f_bsize;
		break;
	case _PC_FILESIZEBITS:
		*ap->a_retval = 64;
		break;
	case _PC_REC_INCR_XFER_SIZE:
		*ap->a_retval = ap->a_vp->v_mount->mnt_stat.f_iosize;
		break;
	case _PC_REC_MAX_XFER_SIZE:
		*ap->a_retval = -1;	/* means ``unlimited'' */
		break;
	case _PC_REC_MIN_XFER_SIZE:
		*ap->a_retval = ap->a_vp->v_mount->mnt_stat.f_iosize;
		break;
	case _PC_REC_XFER_ALIGN:
		*ap->a_retval = PAGE_SIZE;
		break;
	case _PC_SYMLINK_MAX:
		*ap->a_retval = MAXPATHLEN;
		break;

	default:
		error = vop_stdpathconf(ap);
		break;
	}
	return (error);
}