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
struct TYPE_4__ {int zv_volsize; int zv_volblocksize; int /*<<< orphan*/ * zv_objset; } ;
typedef  TYPE_1__ zvol_state_t ;
struct maparg {int ma_blks; TYPE_1__* ma_zv; } ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int EIO ; 
 int TRAVERSE_PRE ; 
 int TRAVERSE_PREFETCH_METADATA ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int traverse_dataset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct maparg*) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_free_extents (TYPE_1__*) ; 
 int /*<<< orphan*/  zvol_map_block ; 

__attribute__((used)) static int
zvol_get_lbas(zvol_state_t *zv)
{
	objset_t *os = zv->zv_objset;
	struct maparg	ma;
	int		err;

	ma.ma_zv = zv;
	ma.ma_blks = 0;
	zvol_free_extents(zv);

	/* commit any in-flight changes before traversing the dataset */
	txg_wait_synced(dmu_objset_pool(os), 0);
	err = traverse_dataset(dmu_objset_ds(os), 0,
	    TRAVERSE_PRE | TRAVERSE_PREFETCH_METADATA, zvol_map_block, &ma);
	if (err || ma.ma_blks != (zv->zv_volsize / zv->zv_volblocksize)) {
		zvol_free_extents(zv);
		return (err ? err : EIO);
	}

	return (0);
}