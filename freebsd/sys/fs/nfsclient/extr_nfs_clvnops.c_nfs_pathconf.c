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
struct vop_pathconf_args {int a_name; int* a_retval; struct vnode* a_vp; } ;
struct vnode {TYPE_2__* v_mount; int /*<<< orphan*/  v_type; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nfsvattr {int /*<<< orphan*/  na_suppattr; } ;
struct nfsv3_pathconf {int pc_linkmax; int pc_namemax; int pc_notrunc; int pc_chownrestricted; int pc_casepreserving; scalar_t__ pc_caseinsensitive; } ;
struct TYPE_3__ {int f_bsize; int f_iosize; } ;
struct TYPE_4__ {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int ACL_MAX_ENTRIES ; 
 int EINVAL ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFSATTRBIT_ACL ; 
 int /*<<< orphan*/  NFSISSET_ATTRBIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NFS_ISV34 (struct vnode*) ; 
 scalar_t__ NFS_ISV4 (struct vnode*) ; 
 int NFS_LINK_MAX ; 
 int NFS_MAXNAMLEN ; 
 int NFS_MAXPATHLEN ; 
 int PAGE_SIZE ; 
 int PIPE_BUF ; 
 int /*<<< orphan*/  VDIR ; 
 int /*<<< orphan*/  VFIFO ; 
#define  _PC_ACL_NFS4 143 
#define  _PC_ACL_PATH_MAX 142 
#define  _PC_ALLOC_SIZE_MIN 141 
#define  _PC_CHOWN_RESTRICTED 140 
#define  _PC_FILESIZEBITS 139 
#define  _PC_LINK_MAX 138 
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
 struct thread* curthread ; 
 int /*<<< orphan*/  nfscl_loadattrcache (struct vnode**,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfsrpc_pathconf (struct vnode*,struct nfsv3_pathconf*,int /*<<< orphan*/ ,struct thread*,struct nfsvattr*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrv_useacl ; 
 int vop_stdpathconf (struct vop_pathconf_args*) ; 

__attribute__((used)) static int
nfs_pathconf(struct vop_pathconf_args *ap)
{
	struct nfsv3_pathconf pc;
	struct nfsvattr nfsva;
	struct vnode *vp = ap->a_vp;
	struct thread *td = curthread;
	int attrflag, error;

	if ((NFS_ISV34(vp) && (ap->a_name == _PC_LINK_MAX ||
	    ap->a_name == _PC_NAME_MAX || ap->a_name == _PC_CHOWN_RESTRICTED ||
	    ap->a_name == _PC_NO_TRUNC)) ||
	    (NFS_ISV4(vp) && ap->a_name == _PC_ACL_NFS4)) {
		/*
		 * Since only the above 4 a_names are returned by the NFSv3
		 * Pathconf RPC, there is no point in doing it for others.
		 * For NFSv4, the Pathconf RPC (actually a Getattr Op.) can
		 * be used for _PC_NFS4_ACL as well.
		 */
		error = nfsrpc_pathconf(vp, &pc, td->td_ucred, td, &nfsva,
		    &attrflag, NULL);
		if (attrflag != 0)
			(void) nfscl_loadattrcache(&vp, &nfsva, NULL, NULL, 0,
			    1);
		if (error != 0)
			return (error);
	} else {
		/*
		 * For NFSv2 (or NFSv3 when not one of the above 4 a_names),
		 * just fake them.
		 */
		pc.pc_linkmax = NFS_LINK_MAX;
		pc.pc_namemax = NFS_MAXNAMLEN;
		pc.pc_notrunc = 1;
		pc.pc_chownrestricted = 1;
		pc.pc_caseinsensitive = 0;
		pc.pc_casepreserving = 1;
		error = 0;
	}
	switch (ap->a_name) {
	case _PC_LINK_MAX:
#ifdef _LP64
		*ap->a_retval = pc.pc_linkmax;
#else
		*ap->a_retval = MIN(LONG_MAX, pc.pc_linkmax);
#endif
		break;
	case _PC_NAME_MAX:
		*ap->a_retval = pc.pc_namemax;
		break;
	case _PC_PIPE_BUF:
		if (ap->a_vp->v_type == VDIR || ap->a_vp->v_type == VFIFO)
			*ap->a_retval = PIPE_BUF;
		else
			error = EINVAL;
		break;
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = pc.pc_chownrestricted;
		break;
	case _PC_NO_TRUNC:
		*ap->a_retval = pc.pc_notrunc;
		break;
	case _PC_ACL_NFS4:
		if (NFS_ISV4(vp) && nfsrv_useacl != 0 && attrflag != 0 &&
		    NFSISSET_ATTRBIT(&nfsva.na_suppattr, NFSATTRBIT_ACL))
			*ap->a_retval = 1;
		else
			*ap->a_retval = 0;
		break;
	case _PC_ACL_PATH_MAX:
		if (NFS_ISV4(vp))
			*ap->a_retval = ACL_MAX_ENTRIES;
		else
			*ap->a_retval = 3;
		break;
	case _PC_PRIO_IO:
		*ap->a_retval = 0;
		break;
	case _PC_SYNC_IO:
		*ap->a_retval = 0;
		break;
	case _PC_ALLOC_SIZE_MIN:
		*ap->a_retval = vp->v_mount->mnt_stat.f_bsize;
		break;
	case _PC_FILESIZEBITS:
		if (NFS_ISV34(vp))
			*ap->a_retval = 64;
		else
			*ap->a_retval = 32;
		break;
	case _PC_REC_INCR_XFER_SIZE:
		*ap->a_retval = vp->v_mount->mnt_stat.f_iosize;
		break;
	case _PC_REC_MAX_XFER_SIZE:
		*ap->a_retval = -1; /* means ``unlimited'' */
		break;
	case _PC_REC_MIN_XFER_SIZE:
		*ap->a_retval = vp->v_mount->mnt_stat.f_iosize;
		break;
	case _PC_REC_XFER_ALIGN:
		*ap->a_retval = PAGE_SIZE;
		break;
	case _PC_SYMLINK_MAX:
		*ap->a_retval = NFS_MAXPATHLEN;
		break;

	default:
		error = vop_stdpathconf(ap);
		break;
	}
	return (error);
}