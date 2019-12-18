#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  tree_conflicted_abspaths; int /*<<< orphan*/  added_abspaths; int /*<<< orphan*/  skipped_abspaths; int /*<<< orphan*/  merged_abspaths; } ;
typedef  TYPE_1__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ path_is_subtree (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
subtree_touched_by_merge(const char *local_abspath,
                         merge_cmd_baton_t *merge_b,
                         apr_pool_t *pool)
{
  return (path_is_subtree(local_abspath, merge_b->merged_abspaths, pool)
          || path_is_subtree(local_abspath, merge_b->skipped_abspaths, pool)
          || path_is_subtree(local_abspath, merge_b->added_abspaths, pool)
          || path_is_subtree(local_abspath, merge_b->tree_conflicted_abspaths,
                             pool));
}