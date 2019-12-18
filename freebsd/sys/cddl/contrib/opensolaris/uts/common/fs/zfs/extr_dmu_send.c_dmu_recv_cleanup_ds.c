#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* drc_ds; scalar_t__ drc_resumable; } ;
typedef  TYPE_2__ dmu_recv_cookie_t ;
struct TYPE_8__ {TYPE_1__* ds_dir; } ;
struct TYPE_6__ {int /*<<< orphan*/  dd_pool; } ;

/* Variables and functions */
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  dmu_recv_tag ; 
 int /*<<< orphan*/  dsl_dataset_disown (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_name (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dsl_destroy_head (char*) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dmu_recv_cleanup_ds(dmu_recv_cookie_t *drc)
{
	if (drc->drc_resumable) {
		/* wait for our resume state to be written to disk */
		txg_wait_synced(drc->drc_ds->ds_dir->dd_pool, 0);
		dsl_dataset_disown(drc->drc_ds, dmu_recv_tag);
	} else {
		char name[ZFS_MAX_DATASET_NAME_LEN];
		dsl_dataset_name(drc->drc_ds, name);
		dsl_dataset_disown(drc->drc_ds, dmu_recv_tag);
		(void) dsl_destroy_head(name);
	}
}