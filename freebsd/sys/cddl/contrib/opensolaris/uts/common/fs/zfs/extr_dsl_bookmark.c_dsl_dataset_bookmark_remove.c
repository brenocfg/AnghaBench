#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  matchtype_t ;
struct TYPE_9__ {int /*<<< orphan*/  ds_bookmarks; TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_10__ {int ds_flags; } ;
struct TYPE_8__ {TYPE_1__* dd_pool; } ;
struct TYPE_7__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int DS_FLAG_CI_DATASET ; 
 int /*<<< orphan*/  MT_NORMALIZE ; 
 TYPE_4__* dsl_dataset_phys (TYPE_3__*) ; 
 int zap_remove_norm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dsl_dataset_bookmark_remove(dsl_dataset_t *ds, const char *name, dmu_tx_t *tx)
{
	objset_t *mos = ds->ds_dir->dd_pool->dp_meta_objset;
	uint64_t bmark_zapobj = ds->ds_bookmarks;
	matchtype_t mt = 0;

	if (dsl_dataset_phys(ds)->ds_flags & DS_FLAG_CI_DATASET)
		mt = MT_NORMALIZE;

	return (zap_remove_norm(mos, bmark_zapobj, name, mt, tx));
}