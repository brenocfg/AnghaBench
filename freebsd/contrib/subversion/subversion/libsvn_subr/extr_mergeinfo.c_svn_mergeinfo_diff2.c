#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_mergeinfo_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walk_mergeinfo_hash_for_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_mergeinfo_diff2(svn_mergeinfo_t *deleted, svn_mergeinfo_t *added,
                    svn_mergeinfo_t from, svn_mergeinfo_t to,
                    svn_boolean_t consider_inheritance,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  if (from && to == NULL)
    {
      *deleted = svn_mergeinfo_dup(from, result_pool);
      *added = svn_hash__make(result_pool);
    }
  else if (from == NULL && to)
    {
      *deleted = svn_hash__make(result_pool);
      *added = svn_mergeinfo_dup(to, result_pool);
    }
  else
    {
      *deleted = svn_hash__make(result_pool);
      *added = svn_hash__make(result_pool);

      if (from && to)
        {
          SVN_ERR(walk_mergeinfo_hash_for_diff(from, to, *deleted, *added,
                                               consider_inheritance,
                                               result_pool, scratch_pool));
        }
    }

  return SVN_NO_ERROR;
}