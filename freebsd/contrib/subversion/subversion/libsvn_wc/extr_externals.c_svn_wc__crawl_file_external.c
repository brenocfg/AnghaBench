#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
struct TYPE_24__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_25__ {int /*<<< orphan*/ * token; } ;
typedef  TYPE_2__ svn_wc__db_lock_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_26__ {TYPE_4__* (* finish_report ) (void*,int /*<<< orphan*/ *) ;TYPE_4__* (* link_path ) (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_4__* (* set_path ) (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_4__* (* delete_path ) (void*,char*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ svn_ra_reporter3_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_27__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_4__*) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 scalar_t__ SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 TYPE_4__* SVN_NO_ERROR ; 
 TYPE_4__* stub1 (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub2 (void*,char*,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub3 (void*,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub4 (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub5 (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub6 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 TYPE_4__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__db_base_get_info (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc_restore (TYPE_1__*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__crawl_file_external(svn_wc_context_t *wc_ctx,
                            const char *local_abspath,
                            const svn_ra_reporter3_t *reporter,
                            void *report_baton,
                            svn_boolean_t restore_files,
                            svn_boolean_t use_commit_times,
                            svn_cancel_func_t cancel_func,
                            void *cancel_baton,
                            svn_wc_notify_func2_t notify_func,
                            void *notify_baton,
                            apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db = wc_ctx->db;
  svn_error_t *err;
  svn_node_kind_t kind;
  svn_wc__db_lock_t *lock;
  svn_revnum_t revision;
  const char *repos_root_url;
  const char *repos_relpath;
  svn_boolean_t update_root;

  err = svn_wc__db_base_get_info(NULL, &kind, &revision,
                                 &repos_relpath, &repos_root_url, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, &lock,
                                 NULL, NULL, &update_root,
                                 db, local_abspath,
                                 scratch_pool, scratch_pool);

  if (err
      || kind == svn_node_dir
      || !update_root)
    {
      if (err && err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
        return svn_error_trace(err);

      svn_error_clear(err);

      /* We don't know about this node, so all we have to do is tell
         the reporter that we don't know this node.

         But first we have to start the report by sending some basic
         information for the root. */

      SVN_ERR(reporter->set_path(report_baton, "", 0, svn_depth_infinity,
                                 FALSE, NULL, scratch_pool));
      SVN_ERR(reporter->delete_path(report_baton, "", scratch_pool));

      /* Finish the report, which causes the update editor to be
         driven. */
      SVN_ERR(reporter->finish_report(report_baton, scratch_pool));

      return SVN_NO_ERROR;
    }
  else
    {
      if (restore_files)
        {
          svn_node_kind_t disk_kind;
          SVN_ERR(svn_io_check_path(local_abspath, &disk_kind, scratch_pool));

          if (disk_kind == svn_node_none)
            {
              err = svn_wc_restore(wc_ctx, local_abspath, use_commit_times,
                                   scratch_pool);

              if (err)
                {
                  if (err->apr_err != SVN_ERR_WC_PATH_UNEXPECTED_STATUS)
                    return svn_error_trace(err);

                  svn_error_clear(err);
                }
            }
        }

      /* Report that we know the path */
      SVN_ERR(reporter->set_path(report_baton, "", revision,
                                 svn_depth_infinity, FALSE, NULL,
                                 scratch_pool));

      /* For compatibility with the normal update editor report we report
         the target as switched.

         ### We can probably report a parent url and unswitched later */
      SVN_ERR(reporter->link_path(report_baton, "",
                                  svn_path_url_add_component2(repos_root_url,
                                                              repos_relpath,
                                                              scratch_pool),
                                  revision,
                                  svn_depth_infinity,
                                  FALSE /* start_empty*/,
                                  lock ? lock->token : NULL,
                                  scratch_pool));
    }

  return svn_error_trace(reporter->finish_report(report_baton, scratch_pool));
}