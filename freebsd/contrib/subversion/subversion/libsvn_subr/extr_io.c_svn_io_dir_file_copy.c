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

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_copy_file (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_dir_file_copy(const char *src_path,
                     const char *dest_path,
                     const char *file,
                     apr_pool_t *pool)
{
  const char *file_dest_path = svn_dirent_join(dest_path, file, pool);
  const char *file_src_path = svn_dirent_join(src_path, file, pool);

  return svn_error_trace(
            svn_io_copy_file(file_src_path, file_dest_path, TRUE, pool));
}