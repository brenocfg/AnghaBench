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
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_run_diff3_3 (int*,char const*,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_run_diff3_2(int *exitcode,
                   const char *dir,
                   const char *mine,
                   const char *older,
                   const char *yours,
                   const char *mine_label,
                   const char *older_label,
                   const char *yours_label,
                   apr_file_t *merged,
                   const char *diff3_cmd,
                   const apr_array_header_t *user_args,
                   apr_pool_t *pool)
{
  SVN_ERR(svn_path_cstring_to_utf8(&diff3_cmd, diff3_cmd, pool));

  return svn_error_trace(svn_io_run_diff3_3(exitcode, dir,
                                            mine, older, yours,
                                            mine_label, older_label,
                                            yours_label, merged,
                                            diff3_cmd, user_args, pool));
}