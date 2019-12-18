#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int written_since_error_check; int may_check_for_error; scalar_t__ error_check_interval; int /*<<< orphan*/  block_baton; int /*<<< orphan*/  (* block_handler ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  stream; int /*<<< orphan*/  current_out; TYPE_2__* session; } ;
typedef  TYPE_1__ svn_ra_svn_conn_t ;
struct TYPE_8__ {scalar_t__ bytes_read; scalar_t__ bytes_written; TYPE_3__* callbacks; int /*<<< orphan*/  callbacks_baton; } ;
typedef  TYPE_2__ svn_ra_svn__session_baton_t ;
struct TYPE_9__ {int /*<<< orphan*/  progress_baton; int /*<<< orphan*/  (* progress_func ) (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* cancel_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ svn_ra_callbacks2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  check_io_limits (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__stream_write (int /*<<< orphan*/ ,char const*,int*) ; 

__attribute__((used)) static svn_error_t *writebuf_output(svn_ra_svn_conn_t *conn, apr_pool_t *pool,
                                    const char *data, apr_size_t len)
{
  const char *end = data + len;
  apr_size_t count;
  apr_pool_t *subpool = NULL;
  svn_ra_svn__session_baton_t *session = conn->session;

  /* Limit the size of the response, if a limit has been configured.
   * This is to limit the server load in case users e.g. accidentally ran
   * an export on the root folder. */
  conn->current_out += len;
  SVN_ERR(check_io_limits(conn));

  while (data < end)
    {
      count = end - data;

      if (session && session->callbacks && session->callbacks->cancel_func)
        SVN_ERR((session->callbacks->cancel_func)(session->callbacks_baton));

      SVN_ERR(svn_ra_svn__stream_write(conn->stream, data, &count));
      if (count == 0)
        {
          if (!subpool)
            subpool = svn_pool_create(pool);
          else
            svn_pool_clear(subpool);
          SVN_ERR(conn->block_handler(conn, subpool, conn->block_baton));
        }
      data += count;

      if (session)
        {
          const svn_ra_callbacks2_t *cb = session->callbacks;
          session->bytes_written += count;

          if (cb && cb->progress_func)
            (cb->progress_func)(session->bytes_written + session->bytes_read,
                                -1, cb->progress_baton, subpool);
        }
    }

  conn->written_since_error_check += len;
  conn->may_check_for_error
    = conn->written_since_error_check >= conn->error_check_interval;

  if (subpool)
    svn_pool_destroy(subpool);
  return SVN_NO_ERROR;
}