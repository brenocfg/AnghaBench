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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_DELTA_COMPRESSION_LEVEL_DEFAULT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_open_stdin (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_file_open_stdout (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_ra_svn__flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_svn__write_cmd_failure (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_svn_create_conn5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_child_process_error(apr_pool_t *pool, apr_status_t status,
                                       const char *desc)
{
  svn_ra_svn_conn_t *conn;
  apr_file_t *in_file, *out_file;
  svn_stream_t *in_stream, *out_stream;
  svn_error_t *err;

  if (apr_file_open_stdin(&in_file, pool)
      || apr_file_open_stdout(&out_file, pool))
    return;

  in_stream = svn_stream_from_aprfile2(in_file, FALSE, pool);
  out_stream = svn_stream_from_aprfile2(out_file, FALSE, pool);

  conn = svn_ra_svn_create_conn5(NULL, in_stream, out_stream,
                                 SVN_DELTA_COMPRESSION_LEVEL_DEFAULT, 0,
                                 0, 0, 0, pool);
  err = svn_error_wrap_apr(status, _("Error in child process: %s"), desc);
  svn_error_clear(svn_ra_svn__write_cmd_failure(conn, pool, err));
  svn_error_clear(err);
  svn_error_clear(svn_ra_svn__flush(conn, pool));
}