#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {struct install_baton_t* baton; } ;
typedef  TYPE_2__ svn_stream_t ;
struct TYPE_20__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_18__ {int /*<<< orphan*/  file; } ;
struct install_baton_t {int /*<<< orphan*/  tmp_path; TYPE_1__ baton_apr; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ENOENT (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_UNSUPPORTED_FEATURE ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_compose_create (TYPE_3__*,TYPE_3__*) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 TYPE_3__* svn_io__win_rename_open_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_file_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_file_rename2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_make_dir_recursively (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_stream__install_stream(svn_stream_t *install_stream,
                           const char *final_abspath,
                           svn_boolean_t make_parents,
                           apr_pool_t *scratch_pool)
{
  struct install_baton_t *ib = install_stream->baton;
  svn_error_t *err;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(final_abspath));
#ifdef WIN32
  err = svn_io__win_rename_open_file(ib->baton_apr.file,  ib->tmp_path,
                                     final_abspath, scratch_pool);
  if (make_parents && err && APR_STATUS_IS_ENOENT(err->apr_err))
    {
      svn_error_t *err2;

      err2 = svn_io_make_dir_recursively(svn_dirent_dirname(final_abspath,
                                                    scratch_pool),
                                         scratch_pool);

      if (err2)
        return svn_error_trace(svn_error_compose_create(err, err2));
      else
        svn_error_clear(err);

      err = svn_io__win_rename_open_file(ib->baton_apr.file, ib->tmp_path,
                                         final_abspath, scratch_pool);
    }

  /* ### rhuijben: I wouldn't be surprised if we later find out that we
                   have to fall back to close+rename on some specific
                   error values here, to support some non standard NAS
                   and filesystem scenarios. */
  if (err && err->apr_err == SVN_ERR_UNSUPPORTED_FEATURE)
    {
      /* Rename open files is not supported on this platform: fallback to
         svn_io_file_rename2(). */
      svn_error_clear(err);
      err = SVN_NO_ERROR;
    }
  else
    {
      return svn_error_compose_create(err,
                                      svn_io_file_close(ib->baton_apr.file,
                                                        scratch_pool));
    }
#endif

  /* Close temporary file. */
  SVN_ERR(svn_io_file_close(ib->baton_apr.file, scratch_pool));

  err = svn_io_file_rename2(ib->tmp_path, final_abspath, FALSE, scratch_pool);

  /* A missing directory is too common to not cover here. */
  if (make_parents && err && APR_STATUS_IS_ENOENT(err->apr_err))
    {
      svn_error_t *err2;

      err2 = svn_io_make_dir_recursively(svn_dirent_dirname(final_abspath,
                                                            scratch_pool),
                                         scratch_pool);

      if (err2)
        /* Creating directory didn't work: Return all errors */
        return svn_error_trace(svn_error_compose_create(err, err2));
      else
        /* We could create a directory: retry install */
        svn_error_clear(err);

      SVN_ERR(svn_io_file_rename2(ib->tmp_path, final_abspath, FALSE, scratch_pool));
    }
  else
    SVN_ERR(err);

  return SVN_NO_ERROR;
}