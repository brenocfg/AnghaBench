#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  scn_prefetch_queue; int /*<<< orphan*/  scn_queue; int /*<<< orphan*/ * scn_taskq; } ;
typedef  TYPE_1__ dsl_scan_t ;
struct TYPE_7__ {TYPE_1__* dp_scan; } ;
typedef  TYPE_2__ dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  scan_ds_queue_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ *) ; 

void
dsl_scan_fini(dsl_pool_t *dp)
{
	if (dp->dp_scan != NULL) {
		dsl_scan_t *scn = dp->dp_scan;

		if (scn->scn_taskq != NULL)
			taskq_destroy(scn->scn_taskq);
		scan_ds_queue_clear(scn);
		avl_destroy(&scn->scn_queue);
		avl_destroy(&scn->scn_prefetch_queue);

		kmem_free(dp->dp_scan, sizeof (dsl_scan_t));
		dp->dp_scan = NULL;
	}
}