#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  work_item_baton_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_5__ {scalar_t__ next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; TYPE_1__* children; } ;
typedef  TYPE_2__ svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  scalar_t__ apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
struct TYPE_4__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_and_record_fileinfo (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_special_path (char const*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_affected_time (scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_skel__parse_int (scalar_t__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_from_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
run_record_fileinfo(work_item_baton_t *wqb,
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
  apr_time_t set_time = 0;

  local_relpath = apr_pstrmemdup(scratch_pool, arg1->data, arg1->len);

  SVN_ERR(svn_wc__db_from_relpath(&local_abspath, db, wri_abspath,
                                  local_relpath, scratch_pool, scratch_pool));

  if (arg1->next)
    {
      apr_int64_t val;

      SVN_ERR(svn_skel__parse_int(&val, arg1->next, scratch_pool));
      set_time = (apr_time_t)val;
    }

  if (set_time != 0)
    {
      svn_node_kind_t kind;
      svn_boolean_t is_special;

      /* Do not set the timestamp on special files. */
      SVN_ERR(svn_io_check_special_path(local_abspath, &kind, &is_special,
                                        scratch_pool));

      /* Don't set affected time when local_abspath does not exist or is
         a special file */
      if (kind == svn_node_file && !is_special)
        SVN_ERR(svn_io_set_file_affected_time(set_time, local_abspath,
                                              scratch_pool));

      /* Note that we can't use the value we get here for recording as the
         filesystem might have a different timestamp granularity */
    }


  return svn_error_trace(get_and_record_fileinfo(wqb, local_abspath,
                                                 TRUE /* ignore_enoent */,
                                                 scratch_pool));
}