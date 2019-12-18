#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int code; } ;
struct TYPE_14__ {char* method; char* body_type; TYPE_1__ sline; TYPE_5__* header_delegate_baton; int /*<<< orphan*/  header_delegate; TYPE_5__* body_delegate_baton; int /*<<< orphan*/  body_delegate; struct TYPE_14__* response_baton; int /*<<< orphan*/  response_handler; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_15__ {int /*<<< orphan*/  base_revision; int /*<<< orphan*/  prop_changes; TYPE_2__* commit_ctx; int /*<<< orphan*/  path; int /*<<< orphan*/  relpath; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_4__ proppatch_context_t ;
struct TYPE_16__ {char const* result_checksum; TYPE_2__* commit_ctx; int /*<<< orphan*/  relpath; scalar_t__ remote_result_checksum; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  prop_changes; int /*<<< orphan*/  url; scalar_t__ svndiff; int /*<<< orphan*/  copy_path; scalar_t__ added; int /*<<< orphan*/  stream; int /*<<< orphan*/  svndiff_sent; } ;
typedef  TYPE_5__ file_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {int /*<<< orphan*/  open_batons; int /*<<< orphan*/  session; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* SVN_SVNDIFF_MIME_TYPE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_empty_put_body ; 
 int /*<<< orphan*/  proppatch_resource (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_put_headers ; 
 int /*<<< orphan*/  svn_checksum_match (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_serf__create_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__expect_empty_body ; 
 int /*<<< orphan*/  svn_ra_serf__request_body_cleanup (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__request_body_get_delegate (int /*<<< orphan*/ *,TYPE_5__**,scalar_t__) ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
close_file(void *file_baton,
           const char *text_checksum,
           apr_pool_t *scratch_pool)
{
  file_context_t *ctx = file_baton;
  svn_boolean_t put_empty_file = FALSE;

  ctx->result_checksum = text_checksum;

  /* If we got no stream of changes, but this is an added-without-history
   * file, make a note that we'll be PUTting a zero-byte file to the server.
   */
  if ((!ctx->svndiff) && ctx->added && (!ctx->copy_path))
    put_empty_file = TRUE;

  /* If we have a stream of changes, push them to the server... */
  if ((ctx->svndiff || put_empty_file) && !ctx->svndiff_sent)
    {
      svn_ra_serf__handler_t *handler;
      int expected_result;

      handler = svn_ra_serf__create_handler(ctx->commit_ctx->session,
                                            scratch_pool);

      handler->method = "PUT";
      handler->path = ctx->url;

      handler->response_handler = svn_ra_serf__expect_empty_body;
      handler->response_baton = handler;

      if (put_empty_file)
        {
          handler->body_delegate = create_empty_put_body;
          handler->body_delegate_baton = ctx;
          handler->body_type = "text/plain";
        }
      else
        {
          SVN_ERR(svn_stream_close(ctx->stream));

          svn_ra_serf__request_body_get_delegate(&handler->body_delegate,
                                                 &handler->body_delegate_baton,
                                                 ctx->svndiff);
          handler->body_type = SVN_SVNDIFF_MIME_TYPE;
        }

      handler->header_delegate = setup_put_headers;
      handler->header_delegate_baton = ctx;

      SVN_ERR(svn_ra_serf__context_run_one(handler, scratch_pool));

      if (ctx->added && ! ctx->copy_path)
        expected_result = 201; /* Created */
      else
        expected_result = 204; /* Updated */

      if (handler->sline.code != expected_result)
        return svn_error_trace(svn_ra_serf__unexpected_status(handler));
    }

  /* Don't keep open file handles longer than necessary. */
  if (ctx->svndiff)
    SVN_ERR(svn_ra_serf__request_body_cleanup(ctx->svndiff, scratch_pool));

  /* If we had any prop changes, push them via PROPPATCH. */
  if (apr_hash_count(ctx->prop_changes))
    {
      proppatch_context_t *proppatch;

      proppatch = apr_pcalloc(scratch_pool, sizeof(*proppatch));
      proppatch->pool = scratch_pool;
      proppatch->relpath = ctx->relpath;
      proppatch->path = ctx->url;
      proppatch->commit_ctx = ctx->commit_ctx;
      proppatch->prop_changes = ctx->prop_changes;
      proppatch->base_revision = ctx->base_revision;

      SVN_ERR(proppatch_resource(ctx->commit_ctx->session,
                                 proppatch, scratch_pool));
    }

  if (ctx->result_checksum && ctx->remote_result_checksum)
    {
      svn_checksum_t *result_checksum;

      SVN_ERR(svn_checksum_parse_hex(&result_checksum, svn_checksum_md5,
                                     ctx->result_checksum, scratch_pool));

      if (!svn_checksum_match(result_checksum, ctx->remote_result_checksum))
        return svn_checksum_mismatch_err(result_checksum,
                                         ctx->remote_result_checksum,
                                         scratch_pool,
                                         _("Checksum mismatch for '%s'"),
                                         svn_dirent_local_style(ctx->relpath,
                                                                scratch_pool));
    }

  ctx->commit_ctx->open_batons--;

  return SVN_NO_ERROR;
}