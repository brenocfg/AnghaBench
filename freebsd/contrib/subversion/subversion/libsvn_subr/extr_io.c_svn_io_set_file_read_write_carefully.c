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

/* Variables and functions */
 int /*<<< orphan*/ * svn_io_set_file_read_only (char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_set_file_read_write (char const*,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_set_file_read_write_carefully(const char *path,
                                     svn_boolean_t enable_write,
                                     svn_boolean_t ignore_enoent,
                                     apr_pool_t *pool)
{
  if (enable_write)
    return svn_io_set_file_read_write(path, ignore_enoent, pool);
  return svn_io_set_file_read_only(path, ignore_enoent, pool);
}