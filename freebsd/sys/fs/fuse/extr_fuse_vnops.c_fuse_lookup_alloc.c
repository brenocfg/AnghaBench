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
struct fuse_lookup_alloc_arg {int /*<<< orphan*/  vtyp; int /*<<< orphan*/  cnp; int /*<<< orphan*/  nid; int /*<<< orphan*/  feo; } ;

/* Variables and functions */
 int fuse_vnode_get (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vnode**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fuse_lookup_alloc(struct mount *mp, void *arg, int lkflags, struct vnode **vpp)
{
	struct fuse_lookup_alloc_arg *flaa = arg;

	return fuse_vnode_get(mp, flaa->feo, flaa->nid, NULL, vpp, flaa->cnp,
		flaa->vtyp);
}