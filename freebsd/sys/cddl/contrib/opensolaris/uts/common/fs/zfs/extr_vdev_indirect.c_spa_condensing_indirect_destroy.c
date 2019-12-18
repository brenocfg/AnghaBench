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
struct TYPE_4__ {int /*<<< orphan*/ * sci_new_mapping; int /*<<< orphan*/ * sci_new_mapping_entries; } ;
typedef  TYPE_1__ spa_condensing_indirect_t ;

/* Variables and functions */
 int TXG_SIZE ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_indirect_mapping_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_condensing_indirect_destroy(spa_condensing_indirect_t *sci)
{
	for (int i = 0; i < TXG_SIZE; i++)
		list_destroy(&sci->sci_new_mapping_entries[i]);

	if (sci->sci_new_mapping != NULL)
		vdev_indirect_mapping_close(sci->sci_new_mapping);

	kmem_free(sci, sizeof (*sci));
}