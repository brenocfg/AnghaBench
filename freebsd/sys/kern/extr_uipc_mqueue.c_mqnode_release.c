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
struct mqfs_node {scalar_t__ mn_type; int /*<<< orphan*/  mn_refcount; struct mqfs_info* mn_info; } ;
struct mqfs_info {int /*<<< orphan*/  mi_lock; } ;

/* Variables and functions */
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mqfs_destroy (struct mqfs_node*) ; 
 scalar_t__ mqfstype_dir ; 
 scalar_t__ mqfstype_root ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int sx_xlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void
mqnode_release(struct mqfs_node *node)
{
	struct mqfs_info *mqfs;
	int old, exp;

	mqfs = node->mn_info;
	old = atomic_fetchadd_int(&node->mn_refcount, -1);
	if (node->mn_type == mqfstype_dir ||
	    node->mn_type == mqfstype_root)
		exp = 3; /* include . and .. */
	else
		exp = 1;
	if (old == exp) {
		int locked = sx_xlocked(&mqfs->mi_lock);
		if (!locked)
			sx_xlock(&mqfs->mi_lock);
		mqfs_destroy(node);
		if (!locked)
			sx_xunlock(&mqfs->mi_lock);
	}
}