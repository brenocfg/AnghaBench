#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  gme_ds; } ;
typedef  TYPE_1__ guid_map_entry_t ;
typedef  TYPE_1__ avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (TYPE_1__*) ; 
 TYPE_1__* avl_destroy_nodes (TYPE_1__*,void**) ; 
 int /*<<< orphan*/  dsl_dataset_long_rele (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 

__attribute__((used)) static void
free_guid_map_onexit(void *arg)
{
	avl_tree_t *ca = arg;
	void *cookie = NULL;
	guid_map_entry_t *gmep;

	while ((gmep = avl_destroy_nodes(ca, &cookie)) != NULL) {
		dsl_dataset_long_rele(gmep->gme_ds, gmep);
		dsl_dataset_rele(gmep->gme_ds, gmep);
		kmem_free(gmep, sizeof (guid_map_entry_t));
	}
	avl_destroy(ca);
	kmem_free(ca, sizeof (avl_tree_t));
}