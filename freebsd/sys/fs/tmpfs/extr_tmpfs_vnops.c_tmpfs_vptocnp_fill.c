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
struct vnode {int dummy; } ;
struct tmpfs_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_name; } ;
struct tmpfs_dirent {scalar_t__ td_namelen; TYPE_1__ ud; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LK_SHARED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  tmpfs_vn_get_ino_alloc ; 
 int tmpfs_vptocnp_dir (struct tmpfs_node*,struct tmpfs_node*,struct tmpfs_dirent**) ; 
 int vn_vget_ino_gen (struct vnode*,int /*<<< orphan*/ ,struct tmpfs_node*,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
tmpfs_vptocnp_fill(struct vnode *vp, struct tmpfs_node *tn,
    struct tmpfs_node *tnp, char *buf, int *buflen, struct vnode **dvp)
{
	struct tmpfs_dirent *de;
	int error, i;

	error = vn_vget_ino_gen(vp, tmpfs_vn_get_ino_alloc, tnp, LK_SHARED,
	    dvp);
	if (error != 0)
		return (error);
	error = tmpfs_vptocnp_dir(tn, tnp, &de);
	if (error == 0) {
		i = *buflen;
		i -= de->td_namelen;
		if (i < 0) {
			error = ENOMEM;
		} else {
			bcopy(de->ud.td_name, buf + i, de->td_namelen);
			*buflen = i;
		}
	}
	if (error == 0) {
		if (vp != *dvp)
			VOP_UNLOCK(*dvp, 0);
	} else {
		if (vp != *dvp)
			vput(*dvp);
		else
			vrele(vp);
	}
	return (error);
}