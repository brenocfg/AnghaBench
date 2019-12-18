#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  base_checksum; int /*<<< orphan*/  stream; TYPE_1__* commit_ctx; int /*<<< orphan*/  svndiff; } ;
typedef  TYPE_2__ file_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  session; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SERF__REQUEST_BODY_IN_MEM_SIZE ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  negotiate_put_encoding (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__request_body_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__request_body_get_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_disown (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_to_svndiff3 (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
apply_textdelta(void *file_baton,
                const char *base_checksum,
                apr_pool_t *pool,
                svn_txdelta_window_handler_t *handler,
                void **handler_baton)
{
  file_context_t *ctx = file_baton;
  int svndiff_version;
  int compression_level;

  /* Construct a holder for the request body; we'll give it to serf when we
   * close this file.
   *
   * Please note that if this callback is used, large request bodies will
   * be spilled into temporary files (that requires disk space and prevents
   * simultaneous processing by the server and the client).  A better approach
   * that streams the request body is implemented in apply_textdelta_stream().
   * It will be used with most recent servers having the "send result checksum
   * in response to a PUT" capability, and only if the editor driver uses the
   * new callback.
   */
  ctx->svndiff =
    svn_ra_serf__request_body_create(SVN_RA_SERF__REQUEST_BODY_IN_MEM_SIZE,
                                     ctx->pool);
  ctx->stream = svn_ra_serf__request_body_get_stream(ctx->svndiff);

  negotiate_put_encoding(&svndiff_version, &compression_level,
                         ctx->commit_ctx->session);
  /* Disown the stream; we'll close it explicitly in close_file(). */
  svn_txdelta_to_svndiff3(handler, handler_baton,
                          svn_stream_disown(ctx->stream, pool),
                          svndiff_version, compression_level, pool);

  if (base_checksum)
    ctx->base_checksum = apr_pstrdup(ctx->pool, base_checksum);

  return SVN_NO_ERROR;
}