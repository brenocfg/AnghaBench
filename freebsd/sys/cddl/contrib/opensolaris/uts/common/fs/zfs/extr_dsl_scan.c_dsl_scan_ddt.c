#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  longlong_t ;
struct TYPE_20__ {scalar_t__ ddb_class; size_t ddb_checksum; scalar_t__ ddb_cursor; scalar_t__ ddb_type; } ;
struct TYPE_16__ {scalar_t__ scn_ddt_class_max; TYPE_6__ scn_ddt_bookmark; } ;
struct TYPE_17__ {TYPE_2__ scn_phys; scalar_t__ scn_suspending; TYPE_1__* scn_dp; } ;
typedef  TYPE_3__ dsl_scan_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_18__ {int /*<<< orphan*/  ddt_tree; } ;
typedef  TYPE_4__ ddt_t ;
struct TYPE_19__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ ddt_entry_t ;
typedef  TYPE_6__ ddt_bookmark_t ;
struct TYPE_15__ {TYPE_11__* dp_spa; } ;
struct TYPE_14__ {TYPE_4__** spa_ddt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOENT ; 
 int /*<<< orphan*/ * avl_first (int /*<<< orphan*/ *) ; 
 int ddt_walk (TYPE_11__*,TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_scan_check_suspend (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_scan_ddt_entry (TYPE_3__*,size_t,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
dsl_scan_ddt(dsl_scan_t *scn, dmu_tx_t *tx)
{
	ddt_bookmark_t *ddb = &scn->scn_phys.scn_ddt_bookmark;
	ddt_entry_t dde = { 0 };
	int error;
	uint64_t n = 0;

	while ((error = ddt_walk(scn->scn_dp->dp_spa, ddb, &dde)) == 0) {
		ddt_t *ddt;

		if (ddb->ddb_class > scn->scn_phys.scn_ddt_class_max)
			break;
		dprintf("visiting ddb=%llu/%llu/%llu/%llx\n",
		    (longlong_t)ddb->ddb_class,
		    (longlong_t)ddb->ddb_type,
		    (longlong_t)ddb->ddb_checksum,
		    (longlong_t)ddb->ddb_cursor);

		/* There should be no pending changes to the dedup table */
		ddt = scn->scn_dp->dp_spa->spa_ddt[ddb->ddb_checksum];
		ASSERT(avl_first(&ddt->ddt_tree) == NULL);

		dsl_scan_ddt_entry(scn, ddb->ddb_checksum, &dde, tx);
		n++;

		if (dsl_scan_check_suspend(scn, NULL))
			break;
	}

	zfs_dbgmsg("scanned %llu ddt entries with class_max = %u; "
	    "suspending=%u", (longlong_t)n,
	    (int)scn->scn_phys.scn_ddt_class_max, (int)scn->scn_suspending);

	ASSERT(error == 0 || error == ENOENT);
	ASSERT(error != ENOENT ||
	    ddb->ddb_class > scn->scn_phys.scn_ddt_class_max);
}