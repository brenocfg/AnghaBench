#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  spa_ddt_stat_object; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  enum ddt_type { ____Placeholder_ddt_type } ddt_type ;
typedef  enum ddt_class { ____Placeholder_ddt_class } ddt_class ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_8__ {scalar_t__** ddt_object; int /*<<< orphan*/ ** ddt_object_stats; int /*<<< orphan*/ ** ddt_histogram; int /*<<< orphan*/ * ddt_os; TYPE_1__* ddt_spa; } ;
typedef  TYPE_2__ ddt_t ;
typedef  int /*<<< orphan*/  ddt_object_t ;
struct TYPE_9__ {scalar_t__ (* ddt_op_destroy ) (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DDT_NAMELEN ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int ddt_histogram_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ ddt_object_count (TYPE_2__*,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  ddt_object_name (TYPE_2__*,int,int,char*) ; 
 TYPE_3__** ddt_ops ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ddt_object_destroy(ddt_t *ddt, enum ddt_type type, enum ddt_class class,
    dmu_tx_t *tx)
{
	spa_t *spa = ddt->ddt_spa;
	objset_t *os = ddt->ddt_os;
	uint64_t *objectp = &ddt->ddt_object[type][class];
	uint64_t count;
	char name[DDT_NAMELEN];

	ddt_object_name(ddt, type, class, name);

	ASSERT(*objectp != 0);
	VERIFY(ddt_object_count(ddt, type, class, &count) == 0 && count == 0);
	ASSERT(ddt_histogram_empty(&ddt->ddt_histogram[type][class]));
	VERIFY(zap_remove(os, DMU_POOL_DIRECTORY_OBJECT, name, tx) == 0);
	VERIFY(zap_remove(os, spa->spa_ddt_stat_object, name, tx) == 0);
	VERIFY(ddt_ops[type]->ddt_op_destroy(os, *objectp, tx) == 0);
	bzero(&ddt->ddt_object_stats[type][class], sizeof (ddt_object_t));

	*objectp = 0;
}