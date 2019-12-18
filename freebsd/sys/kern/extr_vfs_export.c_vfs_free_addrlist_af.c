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
struct radix_node_head {int /*<<< orphan*/  rh; int /*<<< orphan*/  (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct radix_node_head*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RADIX_NODE_HEAD_DESTROY (struct radix_node_head*) ; 
 int /*<<< orphan*/  RADIX_NODE_HEAD_LOCK (struct radix_node_head*) ; 
 int /*<<< orphan*/  RADIX_NODE_HEAD_UNLOCK (struct radix_node_head*) ; 
 int /*<<< orphan*/  rn_detachhead (void**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct radix_node_head*) ; 
 int /*<<< orphan*/  vfs_free_netcred ; 

__attribute__((used)) static void
vfs_free_addrlist_af(struct radix_node_head **prnh)
{
	struct radix_node_head *rnh;

	rnh = *prnh;
	RADIX_NODE_HEAD_LOCK(rnh);
	(*rnh->rnh_walktree)(&rnh->rh, vfs_free_netcred, rnh);
	RADIX_NODE_HEAD_UNLOCK(rnh);
	RADIX_NODE_HEAD_DESTROY(rnh);
	rn_detachhead((void **)prnh);
	prnh = NULL;
}