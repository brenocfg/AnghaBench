#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  enum ddt_type { ____Placeholder_ddt_type } ddt_type ;
typedef  enum ddt_class { ____Placeholder_ddt_class } ddt_class ;
struct TYPE_11__ {int doi_physical_blocks_512; int doi_fill_count; int doi_data_block_size; } ;
typedef  TYPE_2__ dmu_object_info_t ;
struct TYPE_12__ {int /*<<< orphan*/ ** ddt_histogram; TYPE_1__* ddt_spa; int /*<<< orphan*/  ddt_os; int /*<<< orphan*/ ** ddt_object; TYPE_4__** ddt_object_stats; } ;
typedef  TYPE_3__ ddt_t ;
struct TYPE_13__ {int ddo_dspace; int ddo_mspace; int /*<<< orphan*/  ddo_count; } ;
typedef  TYPE_4__ ddt_object_t ;
typedef  int /*<<< orphan*/  ddt_histogram_t ;
struct TYPE_10__ {int /*<<< orphan*/  spa_ddt_stat_object; } ;

/* Variables and functions */
 int DDT_NAMELEN ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VERIFY0 (int) ; 
 int ddt_object_count (TYPE_3__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ddt_object_info (TYPE_3__*,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ddt_object_name (TYPE_3__*,int,int,char*) ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ddt_object_load(ddt_t *ddt, enum ddt_type type, enum ddt_class class)
{
	ddt_object_t *ddo = &ddt->ddt_object_stats[type][class];
	dmu_object_info_t doi;
	uint64_t count;
	char name[DDT_NAMELEN];
	int error;

	ddt_object_name(ddt, type, class, name);

	error = zap_lookup(ddt->ddt_os, DMU_POOL_DIRECTORY_OBJECT, name,
	    sizeof (uint64_t), 1, &ddt->ddt_object[type][class]);

	if (error != 0)
		return (error);

	VERIFY0(zap_lookup(ddt->ddt_os, ddt->ddt_spa->spa_ddt_stat_object, name,
	    sizeof (uint64_t), sizeof (ddt_histogram_t) / sizeof (uint64_t),
	    &ddt->ddt_histogram[type][class]));

	/*
	 * Seed the cached statistics.
	 */
	VERIFY(ddt_object_info(ddt, type, class, &doi) == 0);

	error = ddt_object_count(ddt, type, class, &count);
	if (error)
		return error;

	ddo->ddo_count = count;
	ddo->ddo_dspace = doi.doi_physical_blocks_512 << 9;
	ddo->ddo_mspace = doi.doi_fill_count * doi.doi_data_block_size;

	return (0);
}