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
struct TYPE_3__ {int /*<<< orphan*/  zl_bp_tree; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int /*<<< orphan*/  zil_bp_node_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
zil_bp_tree_fini(zilog_t *zilog)
{
	avl_tree_t *t = &zilog->zl_bp_tree;
	zil_bp_node_t *zn;
	void *cookie = NULL;

	while ((zn = avl_destroy_nodes(t, &cookie)) != NULL)
		kmem_free(zn, sizeof (zil_bp_node_t));

	avl_destroy(t);
}