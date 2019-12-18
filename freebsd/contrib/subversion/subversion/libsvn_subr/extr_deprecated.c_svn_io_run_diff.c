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
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_run_diff2 (char const*,char const* const*,int,char const*,char const*,char const*,char const*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_run_diff(const char *dir,
                const char *const *user_args,
                int num_user_args,
                const char *label1,
                const char *label2,
                const char *from,
                const char *to,
                int *pexitcode,
                apr_file_t *outfile,
                apr_file_t *errfile,
                const char *diff_cmd,
                apr_pool_t *pool)
{
  SVN_ERR(svn_path_cstring_to_utf8(&diff_cmd, diff_cmd, pool));

  return svn_error_trace(svn_io_run_diff2(dir, user_args, num_user_args,
                                          label1, label2,
                                          from, to, pexitcode,
                                          outfile, errfile, diff_cmd,
                                          pool));
}