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
typedef  int /*<<< orphan*/  uintmax_t ;
struct vop_print_args {struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; } ;
struct TYPE_2__ {scalar_t__ na_fsid; scalar_t__ na_fileid; } ;
struct nfsnode {TYPE_1__ n_vattr; } ;

/* Variables and functions */
 scalar_t__ VFIFO ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  fifo_printinfo (struct vnode*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
nfs_print(struct vop_print_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct nfsnode *np = VTONFS(vp);

	printf("\tfileid %jd fsid 0x%jx", (uintmax_t)np->n_vattr.na_fileid,
	    (uintmax_t)np->n_vattr.na_fsid);
	if (vp->v_type == VFIFO)
		fifo_printinfo(vp);
	printf("\n");
	return (0);
}