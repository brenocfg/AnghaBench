#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_10__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_CREATE ; 
 int APR_LARGEFILE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 char* apr_palloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_io_file_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_io_file_write_full (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
copy_db_file_safely(const char *src_dir,
                    const char *dst_dir,
                    const char *filename,
                    u_int32_t chunksize,
                    svn_boolean_t allow_missing,
                    apr_pool_t *pool)
{
  apr_file_t *s = NULL, *d = NULL;  /* init to null important for APR */
  const char *file_src_path = svn_dirent_join(src_dir, filename, pool);
  const char *file_dst_path = svn_dirent_join(dst_dir, filename, pool);
  svn_error_t *err;
  char *buf;

  /* Open source file.  If it's missing and that's allowed, there's
     nothing more to do here. */
  err = svn_io_file_open(&s, file_src_path,
                         (APR_READ | APR_LARGEFILE),
                         APR_OS_DEFAULT, pool);
  if (err && APR_STATUS_IS_ENOENT(err->apr_err) && allow_missing)
    {
      svn_error_clear(err);
      return SVN_NO_ERROR;
    }
  SVN_ERR(err);

  /* Open destination file. */
  SVN_ERR(svn_io_file_open(&d, file_dst_path, (APR_WRITE | APR_CREATE |
                                               APR_LARGEFILE),
                           APR_OS_DEFAULT, pool));

  /* Allocate our read/write buffer. */
  buf = apr_palloc(pool, chunksize);

  /* Copy bytes till the cows come home. */
  while (1)
    {
      apr_size_t bytes_this_time = chunksize;
      svn_error_t *read_err, *write_err;

      /* Read 'em. */
      if ((read_err = svn_io_file_read(s, buf, &bytes_this_time, pool)))
        {
          if (APR_STATUS_IS_EOF(read_err->apr_err))
            svn_error_clear(read_err);
          else
            {
              svn_error_clear(svn_io_file_close(s, pool));
              svn_error_clear(svn_io_file_close(d, pool));
              return read_err;
            }
        }

      /* Write 'em. */
      if ((write_err = svn_io_file_write_full(d, buf, bytes_this_time, NULL,
                                              pool)))
        {
          svn_error_clear(svn_io_file_close(s, pool));
          svn_error_clear(svn_io_file_close(d, pool));
          return write_err;
        }

      /* read_err is either NULL, or a dangling pointer - but it is only a
         dangling pointer if it used to be an EOF error. */
      if (read_err)
        {
          SVN_ERR(svn_io_file_close(s, pool));
          SVN_ERR(svn_io_file_close(d, pool));
          break;  /* got EOF on read, all files closed, all done. */
        }
    }

  return SVN_NO_ERROR;
}