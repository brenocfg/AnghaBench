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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int APR_CREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_TRUNCATE ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  FS_TYPE_FILENAME ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_fs_type(const char *path, const char *fs_type, apr_pool_t *pool)
{
  const char *filename;
  apr_file_t *file;

  filename = svn_dirent_join(path, FS_TYPE_FILENAME, pool);
  SVN_ERR(svn_io_file_open(&file, filename,
                           APR_WRITE|APR_CREATE|APR_TRUNCATE|APR_BUFFERED,
                           APR_OS_DEFAULT, pool));
  SVN_ERR(svn_io_file_write_full(file, fs_type, strlen(fs_type), NULL,
                                 pool));
  SVN_ERR(svn_io_file_write_full(file, "\n", 1, NULL, pool));
  return svn_error_trace(svn_io_file_close(file, pool));
}