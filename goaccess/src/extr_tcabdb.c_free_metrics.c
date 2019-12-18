#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* metrics; } ;
struct TYPE_3__ {scalar_t__ metric; int /*<<< orphan*/  dbpath; int /*<<< orphan*/  store; } ;
typedef  TYPE_1__ GTCStorageMetric ;
typedef  size_t GModule ;

/* Variables and functions */
 int GSMTRC_TOTAL ; 
 scalar_t__ MTRC_AGENTS ; 
 int /*<<< orphan*/  tc_bdb_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_db_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* tc_storage ; 

__attribute__((used)) static void
free_metrics (GModule module)
{
  int i;
  GTCStorageMetric mtrc;

  for (i = 0; i < GSMTRC_TOTAL; i++) {
    mtrc = tc_storage[module].metrics[i];
#ifdef TCB_MEMHASH
    tc_db_close (mtrc.store, mtrc.dbpath);
#endif
#ifdef TCB_BTREE
    if (mtrc.metric == MTRC_AGENTS)
      tc_bdb_close (mtrc.store, mtrc.dbpath);
    else
      tc_db_close (mtrc.store, mtrc.dbpath);
#endif
  }
}