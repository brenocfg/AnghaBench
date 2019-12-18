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
struct vop_getextattr_args {char* a_name; struct uio* a_uio; struct ucred* a_cred; struct thread* a_td; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct vattr {int dummy; } ;
struct uio {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct smbnode {int n_dosattr; } ;

/* Variables and functions */
 int EINVAL ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int /*<<< orphan*/  VREAD ; 
 struct smbnode* VTOSMB (struct vnode*) ; 
 char* smbfs_atl ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int uiomove (char*,int,struct uio*) ; 

__attribute__((used)) static int
smbfs_getextattr(struct vop_getextattr_args *ap)
/* {
        IN struct vnode *a_vp;
        IN char *a_name;
        INOUT struct uio *a_uio;
        IN struct ucred *a_cred;
        IN struct thread *a_td;
};
*/
{
	struct vnode *vp = ap->a_vp;
	struct thread *td = ap->a_td;
	struct ucred *cred = ap->a_cred;
	struct uio *uio = ap->a_uio;
	const char *name = ap->a_name;
	struct smbnode *np = VTOSMB(vp);
	struct vattr vattr;
	char buf[10];
	int i, attr, error;

	error = VOP_ACCESS(vp, VREAD, cred, td);
	if (error)
		return error;
	error = VOP_GETATTR(vp, &vattr, cred);
	if (error)
		return error;
	if (strcmp(name, "dosattr") == 0) {
		attr = np->n_dosattr;
		for (i = 0; i < 6; i++, attr >>= 1)
			buf[i] = (attr & 1) ? smbfs_atl[i] : '-';
		buf[i] = 0;
		error = uiomove(buf, i, uio);
		
	} else
		error = EINVAL;
	return error;
}