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
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {struct TYPE_3__* parent; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ parent_path_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_base__dag_adjust_mergeinfo_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
adjust_parent_mergeinfo_counts(parent_path_t *parent_path,
                               apr_int64_t count_delta,
                               const char *txn_id,
                               trail_t *trail,
                               apr_pool_t *pool)
{
  apr_pool_t *iterpool;
  parent_path_t *pp = parent_path;

  if (count_delta == 0)
    return SVN_NO_ERROR;

  iterpool = svn_pool_create(pool);

  while (pp)
    {
      svn_pool_clear(iterpool);
      SVN_ERR(svn_fs_base__dag_adjust_mergeinfo_count(pp->node, count_delta,
                                                      txn_id, trail,
                                                      iterpool));
      pp = pp->parent;
    }
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}