#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
struct TYPE_24__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int svn_wc__db_status_t ;
typedef  char const* svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_filesize_t ;
struct TYPE_25__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CANCELLED ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_EXISTS ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_INVALID_SCHEDULE ; 
 int /*<<< orphan*/  SVN_ERR_WC_MIXED_REVISIONS ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 scalar_t__ SVN_IS_VALID_REVNUM (char const*) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* copy_versioned_dir (int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* copy_versioned_file (int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_compose_create (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_createf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ svn_error_find_cause (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 TYPE_2__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_symlink ; 
 TYPE_2__* svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_get_wcroot (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_min_max_revisions (char const**,char const**,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_handle_move_back (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_pristine_transfer (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_read_info (int*,scalar_t__*,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_scan_addition (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svn_wc__db_status_added ; 
#define  svn_wc__db_status_deleted 131 
#define  svn_wc__db_status_excluded 130 
 int svn_wc__db_status_normal ; 
#define  svn_wc__db_status_not_present 129 
#define  svn_wc__db_status_server_excluded 128 
 TYPE_2__* svn_wc__db_temp_wcroot_tempdir (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
copy_or_move(svn_boolean_t *record_move_on_delete,
             svn_wc_context_t *wc_ctx,
             const char *src_abspath,
             const char *dst_abspath,
             svn_boolean_t metadata_only,
             svn_boolean_t is_move,
             svn_boolean_t allow_mixed_revisions,
             svn_cancel_func_t cancel_func,
             void *cancel_baton,
             svn_wc_notify_func2_t notify_func,
             void *notify_baton,
             apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db = wc_ctx->db;
  svn_node_kind_t src_db_kind;
  const char *dstdir_abspath;
  svn_boolean_t conflicted;
  const char *tmpdir_abspath;
  const char *src_wcroot_abspath;
  const char *dst_wcroot_abspath;
  svn_boolean_t within_one_wc;
  svn_wc__db_status_t src_status;
  svn_error_t *err;
  svn_filesize_t recorded_size;
  apr_time_t recorded_time;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(src_abspath));
  SVN_ERR_ASSERT(svn_dirent_is_absolute(dst_abspath));

  dstdir_abspath = svn_dirent_dirname(dst_abspath, scratch_pool);

  /* Ensure DSTDIR_ABSPATH belongs to the same repository as SRC_ABSPATH;
     throw an error if not. */
  {
    svn_wc__db_status_t dstdir_status;
    const char *src_repos_root_url, *dst_repos_root_url;
    const char *src_repos_uuid, *dst_repos_uuid;
    const char *src_repos_relpath;

    err = svn_wc__db_read_info(&src_status, &src_db_kind, NULL,
                               &src_repos_relpath, &src_repos_root_url,
                               &src_repos_uuid, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL,
                               &recorded_size, &recorded_time,
                               NULL, &conflicted, NULL, NULL, NULL, NULL,
                               NULL, NULL,
                               db, src_abspath, scratch_pool, scratch_pool);

    if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
      {
        /* Replicate old error code and text */
        svn_error_clear(err);
        return svn_error_createf(SVN_ERR_ENTRY_NOT_FOUND, NULL,
                                 _("'%s' is not under version control"),
                                 svn_dirent_local_style(src_abspath,
                                                        scratch_pool));
      }
    else
      SVN_ERR(err);

    /* Do this now, as we know the right data is cached */
    SVN_ERR(svn_wc__db_get_wcroot(&src_wcroot_abspath, db, src_abspath,
                                  scratch_pool, scratch_pool));

    switch (src_status)
      {
        case svn_wc__db_status_deleted:
          return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                                   _("Deleted node '%s' can't be copied."),
                                   svn_dirent_local_style(src_abspath,
                                                          scratch_pool));

        case svn_wc__db_status_excluded:
        case svn_wc__db_status_server_excluded:
        case svn_wc__db_status_not_present:
          return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                                   _("The node '%s' was not found."),
                                   svn_dirent_local_style(src_abspath,
                                                          scratch_pool));
        default:
          break;
      }

     if (is_move && ! strcmp(src_abspath, src_wcroot_abspath))
      {
        return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                                 _("'%s' is the root of a working copy and "
                                   "cannot be moved"),
                                   svn_dirent_local_style(src_abspath,
                                                          scratch_pool));
      }
    if (is_move && src_repos_relpath && !src_repos_relpath[0])
      {
        return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                                 _("'%s' represents the repository root "
                                   "and cannot be moved"),
                                 svn_dirent_local_style(src_abspath,
                                                        scratch_pool));
      }

    err = svn_wc__db_read_info(&dstdir_status, NULL, NULL, NULL,
                               &dst_repos_root_url, &dst_repos_uuid, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL,
                               db, dstdir_abspath,
                               scratch_pool, scratch_pool);

    if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
      {
        /* An unversioned destination directory exists on disk. */
        svn_error_clear(err);
        return svn_error_createf(SVN_ERR_ENTRY_NOT_FOUND, NULL,
                                 _("'%s' is not under version control"),
                                 svn_dirent_local_style(dstdir_abspath,
                                                        scratch_pool));
      }
    else
      SVN_ERR(err);

    /* Do this now, as we know the right data is cached */
    SVN_ERR(svn_wc__db_get_wcroot(&dst_wcroot_abspath, db, dstdir_abspath,
                                  scratch_pool, scratch_pool));

    if (!src_repos_root_url)
      {
        if (src_status == svn_wc__db_status_added)
          SVN_ERR(svn_wc__db_scan_addition(NULL, NULL, NULL,
                                           &src_repos_root_url,
                                           &src_repos_uuid, NULL, NULL, NULL,
                                           NULL,
                                           db, src_abspath,
                                           scratch_pool, scratch_pool));
        else
          /* If not added, the node must have a base or we can't copy */
          SVN_ERR(svn_wc__db_base_get_info(NULL, NULL, NULL, NULL,
                                           &src_repos_root_url,
                                           &src_repos_uuid, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL,
                                           db, src_abspath,
                                           scratch_pool, scratch_pool));
      }

    if (!dst_repos_root_url)
      {
        if (dstdir_status == svn_wc__db_status_added)
          SVN_ERR(svn_wc__db_scan_addition(NULL, NULL, NULL,
                                           &dst_repos_root_url,
                                           &dst_repos_uuid, NULL, NULL, NULL,
                                           NULL,
                                           db, dstdir_abspath,
                                           scratch_pool, scratch_pool));
        else
          /* If not added, the node must have a base or we can't copy */
          SVN_ERR(svn_wc__db_base_get_info(NULL, NULL, NULL, NULL,
                                           &dst_repos_root_url,
                                           &dst_repos_uuid, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL,
                                           db, dstdir_abspath,
                                           scratch_pool, scratch_pool));
      }

    if (strcmp(src_repos_root_url, dst_repos_root_url) != 0
        || strcmp(src_repos_uuid, dst_repos_uuid) != 0)
      return svn_error_createf(
         SVN_ERR_WC_INVALID_SCHEDULE, NULL,
         _("Cannot copy to '%s', as it is not from repository '%s'; "
           "it is from '%s'"),
         svn_dirent_local_style(dst_abspath, scratch_pool),
         src_repos_root_url, dst_repos_root_url);

    if (dstdir_status == svn_wc__db_status_deleted)
      return svn_error_createf(
         SVN_ERR_WC_INVALID_SCHEDULE, NULL,
         _("Cannot copy to '%s' as it is scheduled for deletion"),
         svn_dirent_local_style(dst_abspath, scratch_pool));
         /* ### should report dstdir_abspath instead of dst_abspath? */
  }

  /* TODO(#2843): Rework the error report. */
  /* Check if the copy target is missing or hidden and thus not exist on the
     disk, before actually doing the file copy. */
  {
    svn_wc__db_status_t dst_status;

    err = svn_wc__db_read_info(&dst_status, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL,
                               db, dst_abspath, scratch_pool, scratch_pool);

    if (err && err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
      return svn_error_trace(err);

    svn_error_clear(err);

    if (!err)
      switch (dst_status)
        {
          case svn_wc__db_status_excluded:
            return svn_error_createf(
                     SVN_ERR_ENTRY_EXISTS, NULL,
                     _("'%s' is already under version control "
                       "but is excluded."),
                     svn_dirent_local_style(dst_abspath, scratch_pool));
          case svn_wc__db_status_server_excluded:
            return svn_error_createf(
                     SVN_ERR_ENTRY_EXISTS, NULL,
                     _("'%s' is already under version control"),
                     svn_dirent_local_style(dst_abspath, scratch_pool));

          case svn_wc__db_status_deleted:
          case svn_wc__db_status_not_present:
            break; /* OK to add */

          default:
            if (!metadata_only)
              return svn_error_createf(SVN_ERR_ENTRY_EXISTS, NULL,
                                 _("There is already a versioned item '%s'"),
                                 svn_dirent_local_style(dst_abspath,
                                                        scratch_pool));
        }
  }

  /* Check that the target path is not obstructed, if required. */
  if (!metadata_only)
    {
      svn_node_kind_t dst_kind;

      /* (We need only to check the root of the copy, not every path inside
         copy_versioned_file/_dir.) */
      SVN_ERR(svn_io_check_path(dst_abspath, &dst_kind, scratch_pool));
      if (dst_kind != svn_node_none)
        return svn_error_createf(SVN_ERR_ENTRY_EXISTS, NULL,
                                 _("'%s' already exists and is in the way"),
                                 svn_dirent_local_style(dst_abspath,
                                                        scratch_pool));
    }

  SVN_ERR(svn_wc__db_temp_wcroot_tempdir(&tmpdir_abspath, db,
                                         dstdir_abspath,
                                         scratch_pool, scratch_pool));

  within_one_wc = (strcmp(src_wcroot_abspath, dst_wcroot_abspath) == 0);

  if (is_move
      && !within_one_wc)
    {
      if (record_move_on_delete)
        *record_move_on_delete = FALSE;

      is_move = FALSE;
    }

  if (!within_one_wc)
    SVN_ERR(svn_wc__db_pristine_transfer(db, src_abspath, dst_wcroot_abspath,
                                         cancel_func, cancel_baton,
                                         scratch_pool));

  if (src_db_kind == svn_node_file
      || src_db_kind == svn_node_symlink)
    {
      err = copy_versioned_file(db, src_abspath, dst_abspath, dst_abspath,
                                tmpdir_abspath,
                                metadata_only, conflicted, is_move,
                                NULL, recorded_size, recorded_time,
                                cancel_func, cancel_baton,
                                notify_func, notify_baton,
                                scratch_pool);
    }
  else
    {
      if (is_move
          && src_status == svn_wc__db_status_normal)
        {
          svn_revnum_t min_rev;
          svn_revnum_t max_rev;

          /* Verify that the move source is a single-revision subtree. */
          SVN_ERR(svn_wc__db_min_max_revisions(&min_rev, &max_rev, db,
                                               src_abspath, FALSE, scratch_pool));
          if (SVN_IS_VALID_REVNUM(min_rev) && SVN_IS_VALID_REVNUM(max_rev) &&
              min_rev != max_rev)
            {
              if (!allow_mixed_revisions)
                return svn_error_createf(SVN_ERR_WC_MIXED_REVISIONS, NULL,
                                         _("Cannot move mixed-revision "
                                           "subtree '%s' [%ld:%ld]; "
                                           "try updating it first"),
                                         svn_dirent_local_style(src_abspath,
                                                                scratch_pool),
                                         min_rev, max_rev);

#ifndef RECORD_MIXED_MOVE
              is_move = FALSE;
              if (record_move_on_delete)
                *record_move_on_delete = FALSE;
#endif
            }
        }

      err = copy_versioned_dir(db, src_abspath, dst_abspath, dst_abspath,
                               tmpdir_abspath, metadata_only, is_move,
                               NULL /* dirent */,
                               cancel_func, cancel_baton,
                               notify_func, notify_baton,
                               scratch_pool);
    }

  if (err && svn_error_find_cause(err, SVN_ERR_CANCELLED))
    return svn_error_trace(err);

  if (is_move)
    err = svn_error_compose_create(err,
                svn_wc__db_op_handle_move_back(NULL,
                                               db, dst_abspath, src_abspath,
                                               NULL /* work_items */,
                                               scratch_pool));

  /* Run the work queue with the remaining work */
  SVN_ERR(svn_error_compose_create(
                                err,
                                svn_wc__wq_run(db, dst_abspath,
                                                   cancel_func, cancel_baton,
                                                   scratch_pool)));

  return SVN_NO_ERROR;
}