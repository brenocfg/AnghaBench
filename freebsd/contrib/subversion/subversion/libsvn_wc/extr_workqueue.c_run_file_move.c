#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  work_item_baton_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_14__ {TYPE_2__* next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; TYPE_1__* children; } ;
typedef  TYPE_3__ svn_skel_t ;
struct TYPE_15__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_3__* next; } ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_4__*) ; 
 TYPE_4__* SVN_NO_ERROR ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_io_file_move (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__db_from_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
run_file_move(work_item_baton_t *wqb,
              svn_wc__db_t *db,
              const svn_skel_t *work_item,
              const char *wri_abspath,
              svn_cancel_func_t cancel_func,
              void *cancel_baton,
              apr_pool_t *scratch_pool)
{
  const svn_skel_t *arg1 = work_item->children->next;
  const char *src_abspath, *dst_abspath;
  const char *local_relpath;
  svn_error_t *err;

  local_relpath = apr_pstrmemdup(scratch_pool, arg1->data, arg1->len);
  SVN_ERR(svn_wc__db_from_relpath(&src_abspath, db, wri_abspath, local_relpath,
                                  scratch_pool, scratch_pool));
  local_relpath = apr_pstrmemdup(scratch_pool, arg1->next->data,
                                 arg1->next->len);
  SVN_ERR(svn_wc__db_from_relpath(&dst_abspath, db, wri_abspath, local_relpath,
                                  scratch_pool, scratch_pool));

  /* Use svn_io_file_move() instead of svn_io_file_rename() to allow cross
     device copies. We should not fail in the workqueue. */

  err = svn_io_file_move(src_abspath, dst_abspath, scratch_pool);

  /* If the source is not found, we assume the wq op is already handled */
  if (err && APR_STATUS_IS_ENOENT(err->apr_err))
    svn_error_clear(err);
  else
    SVN_ERR(err);

  return SVN_NO_ERROR;
}