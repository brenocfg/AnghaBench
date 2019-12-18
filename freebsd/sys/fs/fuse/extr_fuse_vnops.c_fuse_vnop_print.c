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
typedef  int /*<<< orphan*/  uintmax_t ;
struct vop_print_args {int /*<<< orphan*/  a_vp; } ;
struct fuse_vnode_data {int /*<<< orphan*/  flag; scalar_t__ nlookup; scalar_t__ parent_nid; } ;

/* Variables and functions */
 struct fuse_vnode_data* VTOFUD (int /*<<< orphan*/ ) ; 
 scalar_t__ VTOILLU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fuse_vnop_print(struct vop_print_args *ap)
{
	struct fuse_vnode_data *fvdat = VTOFUD(ap->a_vp);

	printf("nodeid: %ju, parent nodeid: %ju, nlookup: %ju, flag: %#x\n",
	    (uintmax_t)VTOILLU(ap->a_vp), (uintmax_t)fvdat->parent_nid,
	    (uintmax_t)fvdat->nlookup,
	    fvdat->flag);

	return 0;
}