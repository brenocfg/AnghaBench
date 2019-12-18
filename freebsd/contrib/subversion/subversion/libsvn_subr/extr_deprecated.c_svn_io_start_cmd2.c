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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_proc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_io_start_cmd3 (int /*<<< orphan*/ *,char const*,char const*,char const* const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_start_cmd2(apr_proc_t *cmd_proc,
                  const char *path,
                  const char *cmd,
                  const char *const *args,
                  svn_boolean_t inherit,
                  svn_boolean_t infile_pipe,
                  apr_file_t *infile,
                  svn_boolean_t outfile_pipe,
                  apr_file_t *outfile,
                  svn_boolean_t errfile_pipe,
                  apr_file_t *errfile,
                  apr_pool_t *pool)
{
  return svn_io_start_cmd3(cmd_proc, path, cmd, args, NULL, inherit,
                           infile_pipe, infile, outfile_pipe, outfile,
                           errfile_pipe, errfile, pool);
}