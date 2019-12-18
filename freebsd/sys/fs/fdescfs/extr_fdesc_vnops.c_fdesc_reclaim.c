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
struct vop_reclaim_args {struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/ * v_data; } ;
struct fdescnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 struct fdescnode* VTOFDESC (struct vnode*) ; 
 int /*<<< orphan*/  fdesc_remove_entry (struct fdescnode*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fdesc_reclaim(struct vop_reclaim_args *ap)
{
	struct vnode *vp;
	struct fdescnode *fd;

 	vp = ap->a_vp;
 	fd = VTOFDESC(vp);
	fdesc_remove_entry(fd);
	free(vp->v_data, M_TEMP);
	vp->v_data = NULL;
	return (0);
}