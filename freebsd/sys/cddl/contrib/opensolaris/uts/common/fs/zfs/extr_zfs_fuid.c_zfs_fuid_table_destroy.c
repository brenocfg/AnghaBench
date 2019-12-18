#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  f_ksid; } ;
typedef  TYPE_1__ fuid_domain_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ksiddomain_rele (int /*<<< orphan*/ ) ; 

void
zfs_fuid_table_destroy(avl_tree_t *idx_tree, avl_tree_t *domain_tree)
{
	fuid_domain_t *domnode;
	void *cookie;

	cookie = NULL;
	while (domnode = avl_destroy_nodes(domain_tree, &cookie))
		ksiddomain_rele(domnode->f_ksid);

	avl_destroy(domain_tree);
	cookie = NULL;
	while (domnode = avl_destroy_nodes(idx_tree, &cookie))
		kmem_free(domnode, sizeof (fuid_domain_t));
	avl_destroy(idx_tree);
}