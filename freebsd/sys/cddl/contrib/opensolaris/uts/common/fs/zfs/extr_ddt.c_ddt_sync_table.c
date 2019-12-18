#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {scalar_t__ ub_version; } ;
struct TYPE_11__ {scalar_t__ spa_ddt_stat_object; TYPE_1__ spa_uberblock; } ;
typedef  TYPE_2__ spa_t ;
typedef  enum ddt_type { ____Placeholder_ddt_type } ddt_type ;
typedef  enum ddt_class { ____Placeholder_ddt_class } ddt_class ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_12__ {int /*<<< orphan*/  ddt_histogram_cache; int /*<<< orphan*/  ddt_histogram; int /*<<< orphan*/  ddt_tree; int /*<<< orphan*/  ddt_os; TYPE_2__* ddt_spa; } ;
typedef  TYPE_3__ ddt_t ;
typedef  int /*<<< orphan*/  ddt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DDT_CLASSES ; 
 int DDT_TYPES ; 
 int /*<<< orphan*/  DMU_OT_DDT_STATS ; 
 int /*<<< orphan*/  DMU_POOL_DDT_STATS ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 scalar_t__ SPA_VERSION_DEDUP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/ * avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ddt_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ddt_object_count (TYPE_3__*,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  ddt_object_destroy (TYPE_3__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ddt_object_exists (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ddt_object_sync (TYPE_3__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_sync_entry (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zap_create_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ddt_sync_table(ddt_t *ddt, dmu_tx_t *tx, uint64_t txg)
{
	spa_t *spa = ddt->ddt_spa;
	ddt_entry_t *dde;
	void *cookie = NULL;

	if (avl_numnodes(&ddt->ddt_tree) == 0)
		return;

	ASSERT(spa->spa_uberblock.ub_version >= SPA_VERSION_DEDUP);

	if (spa->spa_ddt_stat_object == 0) {
		spa->spa_ddt_stat_object = zap_create_link(ddt->ddt_os,
		    DMU_OT_DDT_STATS, DMU_POOL_DIRECTORY_OBJECT,
		    DMU_POOL_DDT_STATS, tx);
	}

	while ((dde = avl_destroy_nodes(&ddt->ddt_tree, &cookie)) != NULL) {
		ddt_sync_entry(ddt, dde, tx, txg);
		ddt_free(dde);
	}

	for (enum ddt_type type = 0; type < DDT_TYPES; type++) {
		uint64_t add, count = 0;
		for (enum ddt_class class = 0; class < DDT_CLASSES; class++) {
			if (ddt_object_exists(ddt, type, class)) {
				ddt_object_sync(ddt, type, class, tx);
				VERIFY(ddt_object_count(ddt, type, class,
				    &add) == 0);
				count += add;
			}
		}
		for (enum ddt_class class = 0; class < DDT_CLASSES; class++) {
			if (count == 0 && ddt_object_exists(ddt, type, class))
				ddt_object_destroy(ddt, type, class, tx);
		}
	}

	bcopy(ddt->ddt_histogram, &ddt->ddt_histogram_cache,
	    sizeof (ddt->ddt_histogram));
}