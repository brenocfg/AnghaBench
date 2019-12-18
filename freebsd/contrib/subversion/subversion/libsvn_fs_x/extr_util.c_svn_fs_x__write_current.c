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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int APR_CREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* svn_fs_x__path_current (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__write_current(svn_fs_t *fs,
                        svn_revnum_t rev,
                        apr_pool_t *scratch_pool)
{
  char *buf;
  const char *tmp_name, *name;
  apr_file_t *file;

  /* Now we can just write out this line. */
  buf = apr_psprintf(scratch_pool, "%ld\n", rev);

  name = svn_fs_x__path_current(fs, scratch_pool);
  tmp_name = svn_fs_x__path_next(fs, scratch_pool);

  SVN_ERR(svn_io_file_open(&file, tmp_name,
                           APR_WRITE | APR_CREATE | APR_BUFFERED,
                           APR_OS_DEFAULT, scratch_pool));
  SVN_ERR(svn_io_file_write_full(file, buf, strlen(buf), NULL,
                                 scratch_pool));
  SVN_ERR(svn_io_file_close(file, scratch_pool));

  /* Copying permissions is a no-op on WIN32. */
  SVN_ERR(svn_io_copy_perms(name, tmp_name, scratch_pool));

  /* Move the file into place. */
  SVN_ERR(svn_io_file_rename2(tmp_name, name, TRUE, scratch_pool));

  return SVN_NO_ERROR;
}