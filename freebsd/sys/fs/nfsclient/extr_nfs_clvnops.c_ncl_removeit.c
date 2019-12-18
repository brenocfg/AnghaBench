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
struct sillyrename {int /*<<< orphan*/  s_cred; int /*<<< orphan*/  s_namlen; int /*<<< orphan*/  s_name; TYPE_1__* s_dvp; } ;
struct TYPE_2__ {scalar_t__ v_type; } ;

/* Variables and functions */
 scalar_t__ VBAD ; 
 int nfs_removerpc (TYPE_1__*,struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
ncl_removeit(struct sillyrename *sp, struct vnode *vp)
{
	/*
	 * Make sure that the directory vnode is still valid.
	 * XXX we should lock sp->s_dvp here.
	 */
	if (sp->s_dvp->v_type == VBAD)
		return (0);
	return (nfs_removerpc(sp->s_dvp, vp, sp->s_name, sp->s_namlen,
	    sp->s_cred, NULL));
}