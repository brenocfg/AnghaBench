#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  u_int ;
struct vnode {int dummy; } ;
struct mount {int dummy; } ;
struct TYPE_3__ {void* sn_parent_id; void* sn_id; } ;
typedef  TYPE_1__ sfs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  sfs_compare_ids ; 
 int vfs_hash_get (struct mount const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct vnode**,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
sfs_vnode_get(const struct mount *mp, int flags, uint64_t parent_id,
   uint64_t id, struct vnode **vpp)
{
	sfs_node_t search;
	int err;

	search.sn_id = id;
	search.sn_parent_id = parent_id;
	err = vfs_hash_get(mp, (u_int)id, flags, curthread, vpp,
	    sfs_compare_ids, &search);
	return (err);
}