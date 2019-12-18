#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  by_extension; } ;
typedef  TYPE_1__ svn_fs_fs__stats_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  initialize_largest_changes (TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_fs_fs__stats_t *
create_stats(apr_pool_t *result_pool)
{
  svn_fs_fs__stats_t *stats = apr_pcalloc(result_pool, sizeof(*stats));

  initialize_largest_changes(stats, 64, result_pool);
  stats->by_extension = apr_hash_make(result_pool);

  return stats;
}