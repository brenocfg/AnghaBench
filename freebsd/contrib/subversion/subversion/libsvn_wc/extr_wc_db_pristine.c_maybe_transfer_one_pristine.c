#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  abspath; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
struct TYPE_24__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STMT_INSERT_OR_IGNORE_PRISTINE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 TYPE_2__* get_pristine_fname (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pristine_get_tempdir (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_error_compose_create (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_io_dir_make (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 TYPE_2__* svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_sqlite__bind_checksum (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_sqlite__bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_sqlite__update (int*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
maybe_transfer_one_pristine(svn_wc__db_wcroot_t *src_wcroot,
                            svn_wc__db_wcroot_t *dst_wcroot,
                            const svn_checksum_t *checksum,
                            const svn_checksum_t *md5_checksum,
                            apr_int64_t size,
                            svn_cancel_func_t cancel_func,
                            void *cancel_baton,
                            apr_pool_t *scratch_pool)
{
  const char *pristine_abspath;
  svn_sqlite__stmt_t *stmt;
  svn_stream_t *src_stream;
  svn_stream_t *dst_stream;
  const char *tmp_abspath;
  const char *src_abspath;
  int affected_rows;
  svn_error_t *err;

  SVN_ERR(svn_sqlite__get_statement(&stmt, dst_wcroot->sdb,
                                    STMT_INSERT_OR_IGNORE_PRISTINE));
  SVN_ERR(svn_sqlite__bind_checksum(stmt, 1, checksum, scratch_pool));
  SVN_ERR(svn_sqlite__bind_checksum(stmt, 2, md5_checksum, scratch_pool));
  SVN_ERR(svn_sqlite__bind_int64(stmt, 3, size));

  SVN_ERR(svn_sqlite__update(&affected_rows, stmt));

  if (affected_rows == 0)
    return SVN_NO_ERROR;

  SVN_ERR(svn_stream_open_unique(&dst_stream, &tmp_abspath,
                                 pristine_get_tempdir(dst_wcroot,
                                                      scratch_pool,
                                                      scratch_pool),
                                 svn_io_file_del_on_pool_cleanup,
                                 scratch_pool, scratch_pool));

  SVN_ERR(get_pristine_fname(&src_abspath, src_wcroot->abspath, checksum,
                             scratch_pool, scratch_pool));

  SVN_ERR(svn_stream_open_readonly(&src_stream, src_abspath,
                                   scratch_pool, scratch_pool));

  /* ### Should we verify the SHA1 or MD5 here, or is that too expensive? */
  SVN_ERR(svn_stream_copy3(src_stream, dst_stream,
                           cancel_func, cancel_baton,
                           scratch_pool));

  SVN_ERR(get_pristine_fname(&pristine_abspath, dst_wcroot->abspath, checksum,
                             scratch_pool, scratch_pool));

  /* Move the file to its target location.  (If it is already there, it is
   * an orphan file and it doesn't matter if we overwrite it.) */
  err = svn_io_file_rename2(tmp_abspath, pristine_abspath, FALSE,
                            scratch_pool);

  /* Maybe the directory doesn't exist yet? */
  if (err && APR_STATUS_IS_ENOENT(err->apr_err))
    {
      svn_error_t *err2;

      err2 = svn_io_dir_make(svn_dirent_dirname(pristine_abspath,
                                                scratch_pool),
                             APR_OS_DEFAULT, scratch_pool);

      if (err2)
        /* Creating directory didn't work: Return all errors */
        return svn_error_trace(svn_error_compose_create(err, err2));
      else
        /* We could create a directory: retry install */
        svn_error_clear(err);

      SVN_ERR(svn_io_file_rename2(tmp_abspath, pristine_abspath, FALSE,
                                  scratch_pool));
    }
  else
    SVN_ERR(err);

  return SVN_NO_ERROR;
}