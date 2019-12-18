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
typedef  int /*<<< orphan*/  svn_fs_x__batch_fsync_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  svn_fs_x__batch_fsync_open_file (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_current (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_next_file(svn_fs_t *fs,
                svn_revnum_t revision,
                svn_fs_x__batch_fsync_t *batch,
                apr_pool_t *scratch_pool)
{
  apr_file_t *file;
  const char *path = svn_fs_x__path_next(fs, scratch_pool);
  const char *perms_path = svn_fs_x__path_current(fs, scratch_pool);
  char *buf;

  /* Create / open the 'next' file. */
  SVN_ERR(svn_fs_x__batch_fsync_open_file(&file, batch, path, scratch_pool));

  /* Write its contents. */
  buf = apr_psprintf(scratch_pool, "%ld\n", revision);
  SVN_ERR(svn_io_file_write_full(file, buf, strlen(buf), NULL, scratch_pool));

  /* Adjust permissions. */
  SVN_ERR(svn_io_copy_perms(perms_path, path, scratch_pool));

  return SVN_NO_ERROR;
}