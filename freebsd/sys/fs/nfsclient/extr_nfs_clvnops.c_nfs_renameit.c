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
struct sillyrename {int /*<<< orphan*/  s_namlen; int /*<<< orphan*/  s_name; } ;
struct componentname {int /*<<< orphan*/  cn_thread; int /*<<< orphan*/  cn_cred; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;

/* Variables and functions */
 int nfs_renamerpc (struct vnode*,struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_renameit(struct vnode *sdvp, struct vnode *svp, struct componentname *scnp,
    struct sillyrename *sp)
{

	return (nfs_renamerpc(sdvp, svp, scnp->cn_nameptr, scnp->cn_namelen,
	    sdvp, NULL, sp->s_name, sp->s_namlen, scnp->cn_cred,
	    scnp->cn_thread));
}