#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  file_deleted; int /*<<< orphan*/  file_changed; int /*<<< orphan*/  file_added; int /*<<< orphan*/  dir_deleted; int /*<<< orphan*/  dir_changed; int /*<<< orphan*/  dir_added; } ;
typedef  TYPE_1__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_12__ {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  config; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  void* svn_boolean_t ;
struct TYPE_14__ {char const* orig_path_1; char const* orig_path_2; int /*<<< orphan*/ * anchor; int /*<<< orphan*/ * session_relpath; } ;
struct TYPE_13__ {char const* header_encoding; char const* relative_to_dir; TYPE_7__ ddi; int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; void* show_copies_as_adds; void* no_diff_deleted; void* no_diff_added; void* use_git_diff_format; void* properties_only; void* ignore_properties; void* force_binary; int /*<<< orphan*/ * errstream; int /*<<< orphan*/ * outstream; int /*<<< orphan*/ * pool; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ diff_writer_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  create_diff_writer_info (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_dir_added ; 
 int /*<<< orphan*/  diff_dir_changed ; 
 int /*<<< orphan*/  diff_dir_deleted ; 
 int /*<<< orphan*/  diff_file_added ; 
 int /*<<< orphan*/  diff_file_changed ; 
 int /*<<< orphan*/  diff_file_deleted ; 
 int /*<<< orphan*/  do_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_diff__tree_processor_create (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_client_diff_peg6(const apr_array_header_t *options,
                     const char *path_or_url,
                     const svn_opt_revision_t *peg_revision,
                     const svn_opt_revision_t *start_revision,
                     const svn_opt_revision_t *end_revision,
                     const char *relative_to_dir,
                     svn_depth_t depth,
                     svn_boolean_t ignore_ancestry,
                     svn_boolean_t no_diff_added,
                     svn_boolean_t no_diff_deleted,
                     svn_boolean_t show_copies_as_adds,
                     svn_boolean_t ignore_content_type,
                     svn_boolean_t ignore_properties,
                     svn_boolean_t properties_only,
                     svn_boolean_t use_git_diff_format,
                     const char *header_encoding,
                     svn_stream_t *outstream,
                     svn_stream_t *errstream,
                     const apr_array_header_t *changelists,
                     svn_client_ctx_t *ctx,
                     apr_pool_t *pool)
{
  diff_writer_info_t dwi = { 0 };
  const svn_diff_tree_processor_t *diff_processor;
  svn_diff_tree_processor_t *processor;

  if (ignore_properties && properties_only)
    return svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL,
                            _("Cannot ignore properties and show only "
                              "properties at the same time"));

  /* setup callback and baton */
  dwi.ddi.orig_path_1 = path_or_url;
  dwi.ddi.orig_path_2 = path_or_url;

  SVN_ERR(create_diff_writer_info(&dwi, options,
                                  ctx->config, pool));
  dwi.pool = pool;
  dwi.outstream = outstream;
  dwi.errstream = errstream;
  dwi.header_encoding = header_encoding;

  dwi.force_binary = ignore_content_type;
  dwi.ignore_properties = ignore_properties;
  dwi.properties_only = properties_only;
  dwi.relative_to_dir = relative_to_dir;
  dwi.use_git_diff_format = use_git_diff_format;
  dwi.no_diff_added = no_diff_added;
  dwi.no_diff_deleted = no_diff_deleted;
  dwi.show_copies_as_adds = show_copies_as_adds;

  dwi.cancel_func = ctx->cancel_func;
  dwi.cancel_baton = ctx->cancel_baton;

  dwi.wc_ctx = ctx->wc_ctx;
  dwi.ddi.session_relpath = NULL;
  dwi.ddi.anchor = NULL;

  processor = svn_diff__tree_processor_create(&dwi, pool);

  processor->dir_added = diff_dir_added;
  processor->dir_changed = diff_dir_changed;
  processor->dir_deleted = diff_dir_deleted;

  processor->file_added = diff_file_added;
  processor->file_changed = diff_file_changed;
  processor->file_deleted = diff_file_deleted;

  diff_processor = processor;

  /* --show-copies-as-adds and --git imply --notice-ancestry */
  if (show_copies_as_adds || use_git_diff_format)
    ignore_ancestry = FALSE;

  return svn_error_trace(do_diff(NULL, NULL, &dwi.ddi,
                                 path_or_url, path_or_url,
                                 start_revision, end_revision,
                                 peg_revision, FALSE /* no_peg_revision */,
                                 depth, ignore_ancestry, changelists,
                                 TRUE /* text_deltas */,
                                 diff_processor, ctx, pool, pool));
}