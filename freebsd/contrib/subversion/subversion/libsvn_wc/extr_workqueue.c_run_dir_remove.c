#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  work_item_baton_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_12__ {scalar_t__ next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; TYPE_1__* children; } ;
typedef  TYPE_2__ svn_skel_t ;
struct TYPE_13__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
struct TYPE_11__ {TYPE_2__* next; } ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_ENOTEMPTY (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN__APR_STATUS_IS_ENOTDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 TYPE_3__* svn_io_dir_remove_nonrecursive (char const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__parse_int (scalar_t__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_from_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
run_dir_remove(work_item_baton_t *wqb,
               svn_wc__db_t *db,
               const svn_skel_t *work_item,
               const char *wri_abspath,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               apr_pool_t *scratch_pool)
{
  const svn_skel_t *arg1 = work_item->children->next;
  const char *local_relpath;
  const char *local_abspath;
  svn_boolean_t recursive;

  local_relpath = apr_pstrmemdup(scratch_pool, arg1->data, arg1->len);
  SVN_ERR(svn_wc__db_from_relpath(&local_abspath, db, wri_abspath,
                                  local_relpath, scratch_pool, scratch_pool));

  recursive = FALSE;
  if (arg1->next)
    {
      apr_int64_t val;
      SVN_ERR(svn_skel__parse_int(&val, arg1->next, scratch_pool));

      recursive = (val != 0);
    }

  /* Remove the path, no worrying if it isn't there.  */
  if (recursive)
    return svn_error_trace(
                svn_io_remove_dir2(local_abspath, TRUE,
                                   cancel_func, cancel_baton,
                                   scratch_pool));
  else
    {
      svn_error_t *err;

      err = svn_io_dir_remove_nonrecursive(local_abspath, scratch_pool);

      if (err && (APR_STATUS_IS_ENOENT(err->apr_err)
                  || SVN__APR_STATUS_IS_ENOTDIR(err->apr_err)
                  || APR_STATUS_IS_ENOTEMPTY(err->apr_err)))
        {
          svn_error_clear(err);
          err = NULL;
        }

      return svn_error_trace(err);
    }
}