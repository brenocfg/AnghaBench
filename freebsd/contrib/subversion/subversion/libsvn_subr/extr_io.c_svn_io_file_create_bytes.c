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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_CREATE ; 
 int APR_EXCL ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_file_write_full (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_file_create_bytes(const char *file,
                         const void *contents,
                         apr_size_t length,
                         apr_pool_t *scratch_pool)
{
  apr_file_t *f;
  apr_size_t written;
  svn_error_t *err = SVN_NO_ERROR;

  SVN_ERR(svn_io_file_open(&f, file,
                           (APR_WRITE | APR_CREATE | APR_EXCL),
                           APR_OS_DEFAULT,
                           scratch_pool));
  if (length)
    err = svn_io_file_write_full(f, contents, length, &written,
                                 scratch_pool);

  err = svn_error_compose_create(
                    err,
                    svn_io_file_close(f, scratch_pool));

  if (err)
    {
      /* Our caller doesn't know if we left a file or not if we return
         an error. Better to cleanup after ourselves if we created the
         file. */
      return svn_error_trace(
                svn_error_compose_create(
                    err,
                    svn_io_remove_file2(file, TRUE, scratch_pool)));
    }

  return SVN_NO_ERROR;
}