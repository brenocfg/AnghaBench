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
struct TYPE_5__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct get_node_mergeinfo_stats_baton {int /*<<< orphan*/  node; int /*<<< orphan*/  child_mergeinfo_count; int /*<<< orphan*/  has_mergeinfo; int /*<<< orphan*/  path; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_mergeinfo_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_get_node_mergeinfo_stats(void *baton, trail_t *trail)
{
  struct get_node_mergeinfo_stats_baton *args = baton;

  SVN_ERR(get_dag(&(args->node), args->root, args->path,
                  trail, trail->pool));
  return svn_fs_base__dag_get_mergeinfo_stats(&(args->has_mergeinfo),
                                              &(args->child_mergeinfo_count),
                                              args->node, trail,
                                              trail->pool);
}