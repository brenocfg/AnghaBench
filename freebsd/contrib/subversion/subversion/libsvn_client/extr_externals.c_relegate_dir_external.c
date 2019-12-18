#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* err; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,TYPE_1__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
struct TYPE_16__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_LEFT_LOCAL_MOD ; 
 scalar_t__ SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 TYPE_3__* svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_open_uniquely_named (int /*<<< orphan*/ *,char const**,char const*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_wc__acquire_write_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__external_remove (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__rename_wc (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_left_local_modifications ; 

__attribute__((used)) static svn_error_t *
relegate_dir_external(svn_wc_context_t *wc_ctx,
                      const char *wri_abspath,
                      const char *local_abspath,
                      svn_cancel_func_t cancel_func,
                      void *cancel_baton,
                      svn_wc_notify_func2_t notify_func,
                      void *notify_baton,
                      apr_pool_t *scratch_pool)
{
  svn_error_t *err = SVN_NO_ERROR;

  SVN_ERR(svn_wc__acquire_write_lock(NULL, wc_ctx, local_abspath,
                                     FALSE, scratch_pool, scratch_pool));

  err = svn_wc__external_remove(wc_ctx, wri_abspath, local_abspath, FALSE,
                                cancel_func, cancel_baton, scratch_pool);
  if (err && (err->apr_err == SVN_ERR_WC_LEFT_LOCAL_MOD))
    {
      const char *parent_dir;
      const char *dirname;
      const char *new_path;

      svn_error_clear(err);
      err = SVN_NO_ERROR;

      svn_dirent_split(&parent_dir, &dirname, local_abspath, scratch_pool);

      /* Reserve the new dir name. */
      SVN_ERR(svn_io_open_uniquely_named(NULL, &new_path,
                                         parent_dir, dirname, ".OLD",
                                         svn_io_file_del_none,
                                         scratch_pool, scratch_pool));

      /* Sigh...  We must fall ever so slightly from grace.

         Ideally, there would be no window, however brief, when we
         don't have a reservation on the new name.  Unfortunately,
         at least in the Unix (Linux?) version of apr_file_rename(),
         you can't rename a directory over a file, because it's just
         calling stdio rename(), which says:

            ENOTDIR
              A  component used as a directory in oldpath or newpath
              path is not, in fact, a directory.  Or, oldpath  is
              a directory, and newpath exists but is not a directory

         So instead, we get the name, then remove the file (ugh), then
         rename the directory, hoping that nobody has gotten that name
         in the meantime -- which would never happen in real life, so
         no big deal.
      */
      /* Do our best, but no biggy if it fails. The rename will fail. */
      svn_error_clear(svn_io_remove_file2(new_path, TRUE, scratch_pool));

      /* Rename. If this is still a working copy we should use the working
         copy rename function (to release open handles) */
      err = svn_wc__rename_wc(wc_ctx, local_abspath, new_path,
                              scratch_pool);

      if (err && err->apr_err == SVN_ERR_WC_PATH_UNEXPECTED_STATUS)
        {
          svn_error_clear(err);

          /* And if it is no longer a working copy, we should just rename
             it */
          err = svn_io_file_rename2(local_abspath, new_path, FALSE, scratch_pool);
        }

      /* ### TODO: We should notify the user about the rename */
      if (notify_func)
        {
          svn_wc_notify_t *notify;

          notify = svn_wc_create_notify(err ? local_abspath : new_path,
                                        svn_wc_notify_left_local_modifications,
                                        scratch_pool);
          notify->kind = svn_node_dir;
          notify->err = err;

          notify_func(notify_baton, notify, scratch_pool);
        }
    }

  return svn_error_trace(err);
}