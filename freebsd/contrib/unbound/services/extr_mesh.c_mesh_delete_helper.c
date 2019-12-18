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
struct mesh_state {int /*<<< orphan*/  s; } ;
struct TYPE_3__ {scalar_t__ key; } ;
typedef  TYPE_1__ rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/  mesh_state_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mesh_delete_helper(rbnode_type* n)
{
	struct mesh_state* mstate = (struct mesh_state*)n->key;
	/* perform a full delete, not only 'cleanup' routine,
	 * because other callbacks expect a clean state in the mesh.
	 * For 're-entrant' calls */
	mesh_state_delete(&mstate->s);
	/* but because these delete the items from the tree, postorder
	 * traversal and rbtree rebalancing do not work together */
}