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
typedef  int /*<<< orphan*/  buf ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__path_min_unpacked_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_read_length_line (int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_revnum_parse (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__read_min_unpacked_rev(svn_revnum_t *min_unpacked_rev,
                                 svn_fs_t *fs,
                                 apr_pool_t *pool)
{
  char buf[80];
  apr_file_t *file;
  apr_size_t len;

  SVN_ERR(svn_io_file_open(&file,
                           svn_fs_fs__path_min_unpacked_rev(fs, pool),
                           APR_READ | APR_BUFFERED,
                           APR_OS_DEFAULT,
                           pool));
  len = sizeof(buf);
  SVN_ERR(svn_io_read_length_line(file, buf, &len, pool));
  SVN_ERR(svn_io_file_close(file, pool));

  SVN_ERR(svn_revnum_parse(min_unpacked_rev, buf, NULL));
  return SVN_NO_ERROR;
}