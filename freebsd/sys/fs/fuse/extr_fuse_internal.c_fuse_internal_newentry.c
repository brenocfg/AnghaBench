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
struct mount {int dummy; } ;
struct fuse_dispatcher {int dummy; } ;
struct componentname {int dummy; } ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;
typedef  enum fuse_opcode { ____Placeholder_fuse_opcode } fuse_opcode ;

/* Variables and functions */
 int /*<<< orphan*/  VTOI (struct vnode*) ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int /*<<< orphan*/ ) ; 
 int fuse_internal_newentry_core (struct vnode*,struct vnode**,struct componentname*,int,struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fuse_internal_newentry_makerequest (struct mount*,int /*<<< orphan*/ ,struct componentname*,int,void*,size_t,struct fuse_dispatcher*) ; 
 struct mount* vnode_mount (struct vnode*) ; 

int
fuse_internal_newentry(struct vnode *dvp,
    struct vnode **vpp,
    struct componentname *cnp,
    enum fuse_opcode op,
    void *buf,
    size_t bufsize,
    enum vtype vtype)
{
	int err;
	struct fuse_dispatcher fdi;
	struct mount *mp = vnode_mount(dvp);

	fdisp_init(&fdi, 0);
	fuse_internal_newentry_makerequest(mp, VTOI(dvp), cnp, op, buf,
	    bufsize, &fdi);
	err = fuse_internal_newentry_core(dvp, vpp, cnp, vtype, &fdi);
	fdisp_destroy(&fdi);

	return err;
}