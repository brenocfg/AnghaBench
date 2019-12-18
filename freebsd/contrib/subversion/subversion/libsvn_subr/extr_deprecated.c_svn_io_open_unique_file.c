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
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 int /*<<< orphan*/  svn_io_file_del_on_close ; 
 int /*<<< orphan*/  svn_io_open_unique_file2 (int /*<<< orphan*/ **,char const**,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_open_unique_file(apr_file_t **file,
                        const char **temp_path,
                        const char *path,
                        const char *suffix,
                        svn_boolean_t delete_on_close,
                        apr_pool_t *pool)
{
  return svn_error_trace(svn_io_open_unique_file2(file, temp_path,
                                                  path, suffix,
                                                  delete_on_close
                                                    ? svn_io_file_del_on_close
                                                    : svn_io_file_del_none,
                                                  pool));
}