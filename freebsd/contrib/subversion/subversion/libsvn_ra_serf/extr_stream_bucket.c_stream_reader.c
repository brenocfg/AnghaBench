#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  errfunc_baton; int /*<<< orphan*/  (* errfunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ stream_bucket_ctx_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EOF ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_ERR_RA_SERF_STREAM_BUCKET_READ_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_read_full (int /*<<< orphan*/ ,char*,scalar_t__*) ; 

__attribute__((used)) static apr_status_t
stream_reader(void *baton, apr_size_t bufsize, char *buf, apr_size_t *len)
{
  stream_bucket_ctx_t *ctx = baton;
  svn_error_t *err;

  *len = bufsize;

  err = svn_stream_read_full(ctx->stream, buf, len);
  if (err)
    {
      if (ctx->errfunc)
        ctx->errfunc(ctx->errfunc_baton, err);
      svn_error_clear(err);

      return SVN_ERR_RA_SERF_STREAM_BUCKET_READ_ERROR;
    }

  if (*len == bufsize)
    {
      return APR_SUCCESS;
    }
  else
    {
      svn_error_clear(svn_stream_close(ctx->stream));
      return APR_EOF;
    }
}