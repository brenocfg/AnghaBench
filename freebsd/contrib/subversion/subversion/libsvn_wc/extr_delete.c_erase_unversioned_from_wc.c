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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_FILENAME ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 

__attribute__((used)) static svn_error_t *
erase_unversioned_from_wc(const char *path,
                          svn_boolean_t ignore_enoent,
                          svn_cancel_func_t cancel_func,
                          void *cancel_baton,
                          apr_pool_t *scratch_pool)
{
  svn_error_t *err;

  /* Optimize the common case: try to delete the file */
  err = svn_io_remove_file2(path, ignore_enoent, scratch_pool);
  if (err)
    {
      /* Then maybe it was a directory? */
      svn_error_clear(err);

      err = svn_io_remove_dir2(path, ignore_enoent, cancel_func, cancel_baton,
                               scratch_pool);

      if (err)
        {
          /* We're unlikely to end up here. But we need this fallback
             to make sure we report the right error *and* try the
             correct deletion at least once. */
          svn_node_kind_t kind;

          svn_error_clear(err);
          SVN_ERR(svn_io_check_path(path, &kind, scratch_pool));
          if (kind == svn_node_file)
            SVN_ERR(svn_io_remove_file2(path, ignore_enoent, scratch_pool));
          else if (kind == svn_node_dir)
            SVN_ERR(svn_io_remove_dir2(path, ignore_enoent,
                                       cancel_func, cancel_baton,
                                       scratch_pool));
          else if (kind == svn_node_none)
            return svn_error_createf(SVN_ERR_BAD_FILENAME, NULL,
                                     _("'%s' does not exist"),
                                     svn_dirent_local_style(path,
                                                            scratch_pool));
          else
            return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                     _("Unsupported node kind for path '%s'"),
                                     svn_dirent_local_style(path,
                                                            scratch_pool));

        }
    }

  return SVN_NO_ERROR;
}