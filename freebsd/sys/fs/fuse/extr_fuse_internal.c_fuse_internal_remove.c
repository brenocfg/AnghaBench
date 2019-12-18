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
struct vnode {int dummy; } ;
struct fuse_dispatcher {scalar_t__ indata; } ;
struct componentname {int cn_namelen; int /*<<< orphan*/  cn_nameptr; int /*<<< orphan*/  cn_cred; int /*<<< orphan*/  cn_thread; } ;
typedef  int nlink_t ;
typedef  enum fuse_opcode { ____Placeholder_fuse_opcode } fuse_opcode ;
struct TYPE_3__ {int /*<<< orphan*/  va_nlink; } ;
struct TYPE_4__ {TYPE_1__ cached_attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FN_CTIMECHANGE ; 
 scalar_t__ VDIR ; 
 TYPE_2__* VTOFUD (struct vnode*) ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int) ; 
 int /*<<< orphan*/  fdisp_make_vp (struct fuse_dispatcher*,int,struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fdisp_wait_answ (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fuse_internal_vnode_disappear (struct vnode*) ; 
 int /*<<< orphan*/  fuse_vnode_clear_attr_cache (struct vnode*) ; 
 int /*<<< orphan*/  fuse_vnode_update (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vnode_vtype (struct vnode*) ; 

int
fuse_internal_remove(struct vnode *dvp,
    struct vnode *vp,
    struct componentname *cnp,
    enum fuse_opcode op)
{
	struct fuse_dispatcher fdi;
	nlink_t nlink;
	int err = 0;

	fdisp_init(&fdi, cnp->cn_namelen + 1);
	fdisp_make_vp(&fdi, op, dvp, cnp->cn_thread, cnp->cn_cred);

	memcpy(fdi.indata, cnp->cn_nameptr, cnp->cn_namelen);
	((char *)fdi.indata)[cnp->cn_namelen] = '\0';

	err = fdisp_wait_answ(&fdi);
	fdisp_destroy(&fdi);

	if (err)
		return (err);

	/* 
	 * Access the cached nlink even if the attr cached has expired.  If
	 * it's inaccurate, the worst that will happen is:
	 * 1) We'll recycle the vnode even though the file has another link we
	 *    don't know about, costing a bit of cpu time, or
	 * 2) We won't recycle the vnode even though all of its links are gone.
	 *    It will linger around until vnlru reclaims it, costing a bit of
	 *    temporary memory.
	 */
	nlink = VTOFUD(vp)->cached_attrs.va_nlink--;

	/* 
	 * Purge the parent's attribute cache because the daemon
	 * should've updated its mtime and ctime.
	 */
	fuse_vnode_clear_attr_cache(dvp);

	/* NB: nlink could be zero if it was never cached */
	if (nlink <= 1 || vnode_vtype(vp) == VDIR) {
		fuse_internal_vnode_disappear(vp);
	} else {
		cache_purge(vp);
		fuse_vnode_update(vp, FN_CTIMECHANGE);
	}

	return err;
}