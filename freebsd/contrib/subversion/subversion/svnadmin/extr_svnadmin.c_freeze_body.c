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
struct freeze_baton_t {int /*<<< orphan*/  status; int /*<<< orphan*/  args; int /*<<< orphan*/  command; } ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_file_open_stderr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_file_open_stdin (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_file_open_stdout (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,char*) ; 
 int /*<<< orphan*/  svn_io_run_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
freeze_body(void *baton,
            apr_pool_t *pool)
{
  struct freeze_baton_t *b = baton;
  apr_status_t apr_err;
  apr_file_t *infile, *outfile, *errfile;

  apr_err = apr_file_open_stdin(&infile, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, "Can't open stdin");
  apr_err = apr_file_open_stdout(&outfile, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, "Can't open stdout");
  apr_err = apr_file_open_stderr(&errfile, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, "Can't open stderr");

  SVN_ERR(svn_io_run_cmd(NULL, b->command, b->args, &b->status,
                         NULL, TRUE,
                         infile, outfile, errfile, pool));

  return SVN_NO_ERROR;
}