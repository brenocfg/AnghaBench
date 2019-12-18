#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {scalar_t__ read_size; scalar_t__ aborted_read_size; int /*<<< orphan*/  result_stream; scalar_t__ aborted_read; TYPE_3__* handler; } ;
typedef  TYPE_2__ stream_ctx_t ;
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
struct TYPE_4__ {int code; } ;
struct TYPE_6__ {TYPE_1__ sline; } ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EAGAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ SERF_BUCKET_READ_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/  serf_bucket_read (int /*<<< orphan*/ *,int,char const**,scalar_t__*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_3__*) ; 
 int /*<<< orphan*/ * svn_ra_serf__wrap_err (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,char const*,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
handle_stream(serf_request_t *request,
              serf_bucket_t *response,
              void *handler_baton,
              apr_pool_t *pool)
{
  stream_ctx_t *fetch_ctx = handler_baton;
  apr_status_t status;

  if (fetch_ctx->handler->sline.code != 200)
    return svn_error_trace(svn_ra_serf__unexpected_status(fetch_ctx->handler));

  while (1)
    {
      const char *data;
      apr_size_t len;

      status = serf_bucket_read(response, 8000, &data, &len);
      if (SERF_BUCKET_READ_ERROR(status))
        {
          return svn_ra_serf__wrap_err(status, NULL);
        }

      fetch_ctx->read_size += len;

      if (fetch_ctx->aborted_read)
        {
          apr_off_t skip;

          /* We haven't caught up to where we were before. */
          if (fetch_ctx->read_size < fetch_ctx->aborted_read_size)
            {
              /* Eek.  What did the file shrink or something? */
              if (APR_STATUS_IS_EOF(status))
                {
                  SVN_ERR_MALFUNCTION();
                }

              /* Skip on to the next iteration of this loop. */
              if (APR_STATUS_IS_EAGAIN(status))
                {
                  return svn_ra_serf__wrap_err(status, NULL);
                }
              continue;
            }

          /* Woo-hoo.  We're back. */
          fetch_ctx->aborted_read = FALSE;

          /* Increment data and len by the difference. */
          skip = len - (fetch_ctx->read_size - fetch_ctx->aborted_read_size);
          data += skip;
          len -= (apr_size_t)skip;
        }

      if (len)
        {
          apr_size_t written_len;

          written_len = len;

          SVN_ERR(svn_stream_write(fetch_ctx->result_stream, data,
                                   &written_len));
        }

      if (status)
        {
          return svn_ra_serf__wrap_err(status, NULL);
        }
    }
  /* not reached */
}