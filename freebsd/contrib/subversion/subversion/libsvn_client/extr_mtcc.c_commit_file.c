#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char const* path; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  scalar_t__ svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* close_file ) (void*,char const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* apply_textdelta ) (void*,char const*,int /*<<< orphan*/ *,scalar_t__*,void**) ;} ;
typedef  TYPE_2__ svn_delta_editor_t ;
struct TYPE_17__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ svn_client_ctx_t ;
struct TYPE_18__ {scalar_t__ kind; } ;
typedef  TYPE_4__ svn_checksum_t ;
struct TYPE_19__ {int /*<<< orphan*/ * base_stream; TYPE_4__* base_checksum; int /*<<< orphan*/ * src_stream; TYPE_4__* src_checksum; } ;
typedef  TYPE_5__ mtcc_op_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  commit_properties (TYPE_2__ const*,TYPE_5__*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,char const*,int /*<<< orphan*/ *,scalar_t__*,void**) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (void*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_checksum_md5 ; 
 char* svn_checksum_to_cstring (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_delta_noop_window_handler ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_checksummed2 (int /*<<< orphan*/ *,TYPE_4__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_run (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,void*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_send_stream (int /*<<< orphan*/ *,scalar_t__,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify_url (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_commit_postfix_txdelta ; 

__attribute__((used)) static svn_error_t *
commit_file(const svn_delta_editor_t *editor,
            mtcc_op_t *op,
            void *file_baton,
            const char *session_url,
            const char *relpath,
            svn_client_ctx_t *ctx,
            apr_pool_t *scratch_pool)
{
  const char *text_checksum = NULL;
  svn_checksum_t *src_checksum = op->src_checksum;
  SVN_ERR(commit_properties(editor, op, file_baton, scratch_pool));

  if (op->src_stream)
    {
      const char *base_checksum = NULL;
      apr_pool_t *txdelta_pool = scratch_pool;
      svn_txdelta_window_handler_t window_handler;
      void *handler_baton;
      svn_stream_t *src_stream = op->src_stream;

      if (op->base_checksum && op->base_checksum->kind == svn_checksum_md5)
        base_checksum = svn_checksum_to_cstring(op->base_checksum, scratch_pool);

      /* ### TODO: Future enhancement: Allocate in special pool and send
                   files after the true edit operation, like a wc commit */
      SVN_ERR(editor->apply_textdelta(file_baton, base_checksum, txdelta_pool,
                                      &window_handler, &handler_baton));

      if (ctx->notify_func2)
        {
          svn_wc_notify_t *notify;

          notify = svn_wc_create_notify_url(
                            svn_path_url_add_component2(session_url, relpath,
                                                        scratch_pool),
                            svn_wc_notify_commit_postfix_txdelta,
                            scratch_pool);

          notify->path = relpath;
          notify->kind = svn_node_file;

          ctx->notify_func2(ctx->notify_baton2, notify, scratch_pool);
        }

      if (window_handler != svn_delta_noop_window_handler)
        {
          if (!src_checksum || src_checksum->kind != svn_checksum_md5)
            src_stream = svn_stream_checksummed2(src_stream, &src_checksum, NULL,
                                                 svn_checksum_md5,
                                                 TRUE, scratch_pool);

          if (!op->base_stream)
            SVN_ERR(svn_txdelta_send_stream(src_stream,
                                            window_handler, handler_baton, NULL,
                                            scratch_pool));
          else
            SVN_ERR(svn_txdelta_run(op->base_stream, src_stream,
                                    window_handler, handler_baton,
                                    svn_checksum_md5, NULL,
                                    ctx->cancel_func, ctx->cancel_baton,
                                    scratch_pool, scratch_pool));
        }

      SVN_ERR(svn_stream_close(src_stream));
      if (op->base_stream)
        SVN_ERR(svn_stream_close(op->base_stream));
    }

  if (src_checksum && src_checksum->kind == svn_checksum_md5)
    text_checksum = svn_checksum_to_cstring(src_checksum, scratch_pool);

  return svn_error_trace(editor->close_file(file_baton, text_checksum,
                                            scratch_pool));
}