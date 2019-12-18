#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ks_private; int /*<<< orphan*/  ks_ndata; int /*<<< orphan*/ * ks_lock; } ;
typedef  TYPE_1__ kstat_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_1__* kstat; int /*<<< orphan*/ * hash; } ;
typedef  TYPE_2__ dbuf_stats_t ;
typedef  int /*<<< orphan*/  dbuf_hash_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  KSTAT_FLAG_VIRTUAL ; 
 int /*<<< orphan*/  KSTAT_TYPE_RAW ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 TYPE_2__ dbuf_stats_hash_table ; 
 int /*<<< orphan*/  dbuf_stats_hash_table_addr ; 
 int /*<<< orphan*/  dbuf_stats_hash_table_data ; 
 int /*<<< orphan*/  dbuf_stats_hash_table_headers ; 
 TYPE_1__* kstat_create (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstat_install (TYPE_1__*) ; 
 int /*<<< orphan*/  kstat_set_raw_ops (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbuf_stats_hash_table_init(dbuf_hash_table_t *hash)
{
	dbuf_stats_t *dsh = &dbuf_stats_hash_table;
	kstat_t *ksp;

	mutex_init(&dsh->lock, NULL, MUTEX_DEFAULT, NULL);
	dsh->hash = hash;

	ksp = kstat_create("zfs", 0, "dbufs", "misc",
	    KSTAT_TYPE_RAW, 0, KSTAT_FLAG_VIRTUAL);
	dsh->kstat = ksp;

	if (ksp) {
		ksp->ks_lock = &dsh->lock;
		ksp->ks_ndata = UINT32_MAX;
		ksp->ks_private = dsh;
		kstat_set_raw_ops(ksp, dbuf_stats_hash_table_headers,
		    dbuf_stats_hash_table_data, dbuf_stats_hash_table_addr);
		kstat_install(ksp);
	}
}