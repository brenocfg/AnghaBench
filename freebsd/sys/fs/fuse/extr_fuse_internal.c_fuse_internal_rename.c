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
struct fuse_rename_in {int /*<<< orphan*/  newdir; } ;
struct fuse_dispatcher {struct fuse_rename_in* indata; } ;
struct componentname {int cn_namelen; int /*<<< orphan*/  cn_nameptr; int /*<<< orphan*/  cn_cred; int /*<<< orphan*/  cn_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_RENAME ; 
 int /*<<< orphan*/  VTOI (struct vnode*) ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int) ; 
 int /*<<< orphan*/  fdisp_make_vp (struct fuse_dispatcher*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fdisp_wait_answ (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

int
fuse_internal_rename(struct vnode *fdvp,
    struct componentname *fcnp,
    struct vnode *tdvp,
    struct componentname *tcnp)
{
	struct fuse_dispatcher fdi;
	struct fuse_rename_in *fri;
	int err = 0;

	fdisp_init(&fdi, sizeof(*fri) + fcnp->cn_namelen + tcnp->cn_namelen + 2);
	fdisp_make_vp(&fdi, FUSE_RENAME, fdvp, tcnp->cn_thread, tcnp->cn_cred);

	fri = fdi.indata;
	fri->newdir = VTOI(tdvp);
	memcpy((char *)fdi.indata + sizeof(*fri), fcnp->cn_nameptr,
	    fcnp->cn_namelen);
	((char *)fdi.indata)[sizeof(*fri) + fcnp->cn_namelen] = '\0';
	memcpy((char *)fdi.indata + sizeof(*fri) + fcnp->cn_namelen + 1,
	    tcnp->cn_nameptr, tcnp->cn_namelen);
	((char *)fdi.indata)[sizeof(*fri) + fcnp->cn_namelen +
	    tcnp->cn_namelen + 1] = '\0';

	err = fdisp_wait_answ(&fdi);
	fdisp_destroy(&fdi);
	return err;
}