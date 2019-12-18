#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
struct TYPE_32__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
struct TYPE_33__ {int /*<<< orphan*/ * token; } ;
typedef  TYPE_2__ svn_wc__db_lock_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_34__ {TYPE_4__* (* abort_report ) (void*,int /*<<< orphan*/ *) ;TYPE_4__* (* finish_report ) (void*,int /*<<< orphan*/ *) ;TYPE_4__* (* set_path ) (void*,char*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_4__* (* link_path ) (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_4__* (* delete_path ) (void*,char*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ svn_ra_reporter3_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_35__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_4__* SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_4__* report_revisions_and_depths (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,char const*,char const*,scalar_t__,TYPE_3__ const*,void*,int,scalar_t__,int,int,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_4__* restore_node (int /*<<< orphan*/ *,char const*,scalar_t__,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_4__* stub1 (void*,char*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub2 (void*,char*,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub3 (void*,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub4 (void*,char*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub5 (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub6 (void*,char*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub7 (void*,int /*<<< orphan*/ *) ; 
 TYPE_4__* stub8 (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_immediates ; 
 scalar_t__ svn_depth_infinity ; 
 scalar_t__ svn_depth_unknown ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_error_compose (TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* svn_error_quick_wrap (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 TYPE_4__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_symlink ; 
 scalar_t__ svn_node_unknown ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__db_base_get_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__db_read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 
 scalar_t__ svn_wc__db_status_not_present ; 

svn_error_t *
svn_wc_crawl_revisions5(svn_wc_context_t *wc_ctx,
                        const char *local_abspath,
                        const svn_ra_reporter3_t *reporter,
                        void *report_baton,
                        svn_boolean_t restore_files,
                        svn_depth_t depth,
                        svn_boolean_t honor_depth_exclude,
                        svn_boolean_t depth_compatibility_trick,
                        svn_boolean_t use_commit_times,
                        svn_cancel_func_t cancel_func,
                        void *cancel_baton,
                        svn_wc_notify_func2_t notify_func,
                        void *notify_baton,
                        apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db = wc_ctx->db;
  svn_error_t *fserr, *err;
  svn_revnum_t target_rev = SVN_INVALID_REVNUM;
  svn_boolean_t start_empty;
  svn_wc__db_status_t status;
  svn_node_kind_t target_kind;
  const char *repos_relpath, *repos_root_url;
  svn_depth_t target_depth;
  svn_wc__db_lock_t *target_lock;
  svn_node_kind_t disk_kind;
  svn_depth_t report_depth;
  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  /* Get the base rev, which is the first revnum that entries will be
     compared to, and some other WC info about the target. */
  err = svn_wc__db_base_get_info(&status, &target_kind, &target_rev,
                                 &repos_relpath, &repos_root_url,
                                 NULL, NULL, NULL, NULL, &target_depth,
                                 NULL, NULL, &target_lock,
                                 NULL, NULL, NULL,
                                 db, local_abspath, scratch_pool,
                                 scratch_pool);

  if (err
      || (status != svn_wc__db_status_normal
          && status != svn_wc__db_status_incomplete))
    {
      if (err && err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
        return svn_error_trace(err);

      svn_error_clear(err);

      /* We don't know about this node, so all we have to do is tell
         the reporter that we don't know this node.

         But first we have to start the report by sending some basic
         information for the root. */

      if (depth == svn_depth_unknown)
        depth = svn_depth_infinity;

      SVN_ERR(reporter->set_path(report_baton, "", 0, depth, FALSE,
                                 NULL, scratch_pool));
      SVN_ERR(reporter->delete_path(report_baton, "", scratch_pool));

      /* Finish the report, which causes the update editor to be
         driven. */
      SVN_ERR(reporter->finish_report(report_baton, scratch_pool));

      return SVN_NO_ERROR;
    }

  if (target_depth == svn_depth_unknown)
    target_depth = svn_depth_infinity;

  start_empty = (status == svn_wc__db_status_incomplete);
  if (depth_compatibility_trick
      && target_depth <= svn_depth_immediates
      && depth > target_depth)
    {
      start_empty = TRUE;
    }

  if (restore_files)
    SVN_ERR(svn_io_check_path(local_abspath, &disk_kind, scratch_pool));
  else
    disk_kind = svn_node_unknown;

  /* Determine if there is a missing node that should be restored */
  if (restore_files
      && disk_kind == svn_node_none)
    {
      svn_wc__db_status_t wrk_status;
      svn_node_kind_t wrk_kind;
      const svn_checksum_t *checksum;
      svn_boolean_t conflicted;

      err = svn_wc__db_read_info(&wrk_status, &wrk_kind, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, &checksum, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, &conflicted, NULL, NULL, NULL, NULL,
                                 NULL, NULL,
                                 db, local_abspath,
                                 scratch_pool, scratch_pool);


      if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
        {
          svn_error_clear(err);
          wrk_status = svn_wc__db_status_not_present;
          wrk_kind = svn_node_file;
        }
      else
        SVN_ERR(err);

      if ((wrk_status == svn_wc__db_status_normal
          || wrk_status == svn_wc__db_status_added
          || wrk_status == svn_wc__db_status_incomplete)
          && (wrk_kind == svn_node_dir || checksum))
        {
          SVN_ERR(restore_node(wc_ctx->db, local_abspath,
                               wrk_kind, conflicted, use_commit_times,
                               cancel_func, cancel_baton,
                               notify_func, notify_baton,
                               scratch_pool));
        }
    }

  {
    report_depth = target_depth;

    if (honor_depth_exclude
        && depth != svn_depth_unknown
        && depth < target_depth)
      report_depth = depth;

    /* The first call to the reporter merely informs it that the
       top-level directory being updated is at BASE_REV.  Its PATH
       argument is ignored. */
    SVN_ERR(reporter->set_path(report_baton, "", target_rev, report_depth,
                               start_empty, NULL, scratch_pool));
  }
  if (target_kind == svn_node_dir)
    {
      if (depth != svn_depth_empty)
        {
          /* Recursively crawl ROOT_DIRECTORY and report differing
             revisions. */
          err = report_revisions_and_depths(wc_ctx->db,
                                            local_abspath,
                                            "",
                                            target_rev,
                                            repos_relpath,
                                            repos_root_url,
                                            report_depth,
                                            reporter, report_baton,
                                            restore_files, depth,
                                            honor_depth_exclude,
                                            depth_compatibility_trick,
                                            start_empty,
                                            use_commit_times,
                                            cancel_func, cancel_baton,
                                            notify_func, notify_baton,
                                            scratch_pool);
          if (err)
            goto abort_report;
        }
    }

  else if (target_kind == svn_node_file || target_kind == svn_node_symlink)
    {
      const char *parent_abspath, *base;
      svn_wc__db_status_t parent_status;
      const char *parent_repos_relpath;

      svn_dirent_split(&parent_abspath, &base, local_abspath,
                       scratch_pool);

      /* We can assume a file is in the same repository as its parent
         directory, so we only look at the relpath. */
      err = svn_wc__db_base_get_info(&parent_status, NULL, NULL,
                                     &parent_repos_relpath, NULL, NULL, NULL,
                                     NULL, NULL, NULL, NULL, NULL, NULL,
                                     NULL, NULL, NULL,
                                     db, parent_abspath,
                                     scratch_pool, scratch_pool);

      if (err)
        goto abort_report;

      if (strcmp(repos_relpath,
                 svn_relpath_join(parent_repos_relpath, base,
                                  scratch_pool)) != 0)
        {
          /* This file is disjoint with respect to its parent
             directory.  Since we are looking at the actual target of
             the report (not some file in a subdirectory of a target
             directory), and that target is a file, we need to pass an
             empty string to link_path. */
          err = reporter->link_path(report_baton,
                                    "",
                                    svn_path_url_add_component2(
                                                    repos_root_url,
                                                    repos_relpath,
                                                    scratch_pool),
                                    target_rev,
                                    svn_depth_infinity,
                                    FALSE,
                                    target_lock ? target_lock->token : NULL,
                                    scratch_pool);
          if (err)
            goto abort_report;
        }
      else if (target_lock)
        {
          /* If this entry is a file node, we just want to report that
             node's revision.  Since we are looking at the actual target
             of the report (not some file in a subdirectory of a target
             directory), and that target is a file, we need to pass an
             empty string to set_path. */
          err = reporter->set_path(report_baton, "", target_rev,
                                   svn_depth_infinity,
                                   FALSE,
                                   target_lock ? target_lock->token : NULL,
                                   scratch_pool);
          if (err)
            goto abort_report;
        }
    }

  /* Finish the report, which causes the update editor to be driven. */
  return svn_error_trace(reporter->finish_report(report_baton, scratch_pool));

 abort_report:
  /* Clean up the fs transaction. */
  if ((fserr = reporter->abort_report(report_baton, scratch_pool)))
    {
      fserr = svn_error_quick_wrap(fserr, _("Error aborting report"));
      svn_error_compose(err, fserr);
    }
  return svn_error_trace(err);
}