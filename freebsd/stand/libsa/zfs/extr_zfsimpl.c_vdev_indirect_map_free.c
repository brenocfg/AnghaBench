#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* io_vsd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_10__ {int is_children; int /*<<< orphan*/  iv_splits; TYPE_4__* is_child; } ;
typedef  TYPE_2__ indirect_vsd_t ;
typedef  TYPE_2__ indirect_split_t ;
struct TYPE_11__ {TYPE_2__* ic_data; } ;
typedef  TYPE_4__ indirect_child_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
vdev_indirect_map_free(zio_t *zio)
{
	indirect_vsd_t *iv = zio->io_vsd;
	indirect_split_t *is;

	while ((is = list_head(&iv->iv_splits)) != NULL) {
		for (int c = 0; c < is->is_children; c++) {
			indirect_child_t *ic = &is->is_child[c];
			free(ic->ic_data);
		}
		list_remove(&iv->iv_splits, is);
		free(is);
	}
	free(iv);
}