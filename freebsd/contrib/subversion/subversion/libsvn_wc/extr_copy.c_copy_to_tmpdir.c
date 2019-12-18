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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_io_file_del_t ;
struct TYPE_3__ {scalar_t__ kind; scalar_t__ filesize; scalar_t__ mtime; scalar_t__ special; } ;
typedef  TYPE_1__ svn_io_dirent2_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNEXPECTED_KIND ; 
 scalar_t__ SVN_INVALID_FILESIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_special_path (char const*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_dir_recursively (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_file (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_link (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_dir_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_del_on_close ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_read_write (char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_unknown ; 
 int /*<<< orphan*/  svn_wc__internal_file_modified_p (scalar_t__*,int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_dir_install (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_file_install (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_file_move (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
copy_to_tmpdir(svn_skel_t **work_item,
               svn_node_kind_t *kind,
               svn_wc__db_t *db,
               const char *src_abspath,
               const char *dst_abspath,
               const char *tmpdir_abspath,
               svn_boolean_t file_copy,
               svn_boolean_t unversioned,
               const svn_io_dirent2_t *dirent,
               svn_filesize_t recorded_size,
               apr_time_t recorded_time,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               apr_pool_t *result_pool,
               apr_pool_t *scratch_pool)
{
  svn_boolean_t is_special;
  svn_io_file_del_t delete_when;
  const char *dst_tmp_abspath;
  svn_node_kind_t dsk_kind;
  if (!kind)
    kind = &dsk_kind;

  *work_item = NULL;

  if (dirent)
    {
      *kind = dirent->kind;
      is_special = dirent->special;
    }
  else
    SVN_ERR(svn_io_check_special_path(src_abspath, kind, &is_special,
                                      scratch_pool));
  if (*kind == svn_node_none)
    {
      return SVN_NO_ERROR;
    }
  else if (*kind == svn_node_unknown)
    {
      return svn_error_createf(SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                               _("Source '%s' is unexpected kind"),
                               svn_dirent_local_style(src_abspath,
                                                      scratch_pool));
    }
  else if (*kind == svn_node_dir || is_special)
    delete_when = svn_io_file_del_on_close;
  else /* the default case: (*kind == svn_node_file) */
    delete_when = svn_io_file_del_none;

  /* ### Do we need a pool cleanup to remove the copy?  We can't use
     ### svn_io_file_del_on_pool_cleanup above because a) it won't
     ### handle the directory case and b) we need to be able to remove
     ### the cleanup before queueing the move work item. */

  if (file_copy && !unversioned)
    {
      svn_boolean_t modified;
      /* It's faster to look for mods on the source now, as
         the timestamp might match, than to examine the
         destination later as the destination timestamp will
         never match. */

      if (dirent
          && dirent->kind == svn_node_file
          && recorded_size != SVN_INVALID_FILESIZE
          && recorded_size == dirent->filesize
          && recorded_time == dirent->mtime)
        {
          modified = FALSE; /* Recorded matches on-disk. Easy out */
        }
      else
        {
          SVN_ERR(svn_wc__internal_file_modified_p(&modified, db, src_abspath,
                                                   FALSE, scratch_pool));
        }

      if (!modified)
        {
          /* Why create a temp copy if we can just reinstall from pristine? */
          SVN_ERR(svn_wc__wq_build_file_install(work_item,
                                                db, dst_abspath, NULL, FALSE,
                                                TRUE,
                                                result_pool, scratch_pool));
          return SVN_NO_ERROR;
        }
    }
  else if (*kind == svn_node_dir && !file_copy)
    {
      /* Just build a new direcory from the workqueue */
      SVN_ERR(svn_wc__wq_build_dir_install(work_item,
                                           db, dst_abspath,
                                           result_pool, scratch_pool));

      return SVN_NO_ERROR;
    }

  /* Set DST_TMP_ABSPATH to a temporary unique path.  If *KIND is file, leave
     a file there and then overwrite it; otherwise leave no node on disk at
     that path.  In the latter case, something else might use that path
     before we get around to using it a moment later, but never mind. */
  SVN_ERR(svn_io_open_unique_file3(NULL, &dst_tmp_abspath, tmpdir_abspath,
                                   delete_when, scratch_pool, scratch_pool));

  if (*kind == svn_node_dir)
    {
      if (file_copy)
        SVN_ERR(svn_io_copy_dir_recursively(
                           src_abspath,
                           tmpdir_abspath,
                           svn_dirent_basename(dst_tmp_abspath, scratch_pool),
                           TRUE, /* copy_perms */
                           cancel_func, cancel_baton,
                           scratch_pool));
      else
        SVN_ERR(svn_io_dir_make(dst_tmp_abspath, APR_OS_DEFAULT, scratch_pool));
    }
  else if (!is_special)
    SVN_ERR(svn_io_copy_file(src_abspath, dst_tmp_abspath,
                             TRUE /* copy_perms */,
                             scratch_pool));
  else
    SVN_ERR(svn_io_copy_link(src_abspath, dst_tmp_abspath, scratch_pool));

  if (file_copy)
    {
      /* Remove 'read-only' from the destination file; it's a local add now. */
      SVN_ERR(svn_io_set_file_read_write(dst_tmp_abspath,
                                         FALSE, scratch_pool));
    }

  SVN_ERR(svn_wc__wq_build_file_move(work_item, db, dst_abspath,
                                     dst_tmp_abspath, dst_abspath,
                                     result_pool, scratch_pool));

  return SVN_NO_ERROR;
}