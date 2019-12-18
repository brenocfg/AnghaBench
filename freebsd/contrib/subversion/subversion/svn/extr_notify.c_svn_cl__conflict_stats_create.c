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
struct TYPE_4__ {scalar_t__ skipped_paths; scalar_t__ tree_conflicts_resolved; scalar_t__ prop_conflicts_resolved; scalar_t__ text_conflicts_resolved; void* tree_conflicts; void* prop_conflicts; void* text_conflicts; int /*<<< orphan*/ * stats_pool; } ;
typedef  TYPE_1__ svn_cl__conflict_stats_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_cl__conflict_stats_t *
svn_cl__conflict_stats_create(apr_pool_t *pool)
{
  svn_cl__conflict_stats_t *conflict_stats
    = apr_palloc(pool, sizeof(*conflict_stats));

  conflict_stats->stats_pool = pool;
  conflict_stats->text_conflicts = apr_hash_make(pool);
  conflict_stats->prop_conflicts = apr_hash_make(pool);
  conflict_stats->tree_conflicts = apr_hash_make(pool);
  conflict_stats->text_conflicts_resolved = 0;
  conflict_stats->prop_conflicts_resolved = 0;
  conflict_stats->tree_conflicts_resolved = 0;
  conflict_stats->skipped_paths = 0;
  return conflict_stats;
}