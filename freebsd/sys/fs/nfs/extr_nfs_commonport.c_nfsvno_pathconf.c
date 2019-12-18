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
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 long NAME_MAX ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 long NFS_LINK_MAX ; 
 int VOP_PATHCONF (struct vnode*,int,long*) ; 
#define  _PC_CHOWN_RESTRICTED 131 
#define  _PC_LINK_MAX 130 
#define  _PC_NAME_MAX 129 
#define  _PC_NO_TRUNC 128 
 int /*<<< orphan*/  printf (char*,int) ; 

int
nfsvno_pathconf(struct vnode *vp, int flag, long *retf,
    struct ucred *cred, struct thread *p)
{
	int error;

	error = VOP_PATHCONF(vp, flag, retf);
	if (error == EOPNOTSUPP || error == EINVAL) {
		/*
		 * Some file systems return EINVAL for name arguments not
		 * supported and some return EOPNOTSUPP for this case.
		 * So the NFSv3 Pathconf RPC doesn't fail for these cases,
		 * just fake them.
		 */
		switch (flag) {
		case _PC_LINK_MAX:
			*retf = NFS_LINK_MAX;
			break;
		case _PC_NAME_MAX:
			*retf = NAME_MAX;
			break;
		case _PC_CHOWN_RESTRICTED:
			*retf = 1;
			break;
		case _PC_NO_TRUNC:
			*retf = 1;
			break;
		default:
			/*
			 * Only happens if a _PC_xxx is added to the server,
			 * but this isn't updated.
			 */
			*retf = 0;
			printf("nfsrvd pathconf flag=%d not supp\n", flag);
		}
		error = 0;
	}
	NFSEXITCODE(error);
	return (error);
}