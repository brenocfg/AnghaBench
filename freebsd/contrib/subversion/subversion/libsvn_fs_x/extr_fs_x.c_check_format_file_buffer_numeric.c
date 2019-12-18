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
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_fs_x__check_file_buffer_numeric (char const*,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
check_format_file_buffer_numeric(const char *buf,
                                 apr_off_t offset,
                                 const char *path,
                                 apr_pool_t *scratch_pool)
{
  return svn_fs_x__check_file_buffer_numeric(buf, offset, path, "Format",
                                             scratch_pool);
}