#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_20__ {int /*<<< orphan*/  (* finish_report ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_path ) (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_ra_reporter3_t ;
struct TYPE_21__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_22__ {int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  close_file; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  add_file; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  open_root; int /*<<< orphan*/  set_target_revision; } ;
typedef  TYPE_3__ svn_delta_editor_t ;
struct TYPE_23__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_4__ svn_client_ctx_t ;
struct TYPE_24__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  repos_root_url; } ;
typedef  TYPE_5__ svn_client__pathrev_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_25__ {int /*<<< orphan*/  dir_count; int /*<<< orphan*/  file_count; } ;
typedef  TYPE_6__ edit_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC (scalar_t__) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_ILLEGAL_URL ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
 int /*<<< orphan*/  change_dir_prop ; 
 int /*<<< orphan*/  change_file_prop ; 
 int /*<<< orphan*/  close_file ; 
 int /*<<< orphan*/  file_write_handler ; 
 int /*<<< orphan*/  open_root ; 
 int /*<<< orphan*/  set_target_revision ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,TYPE_5__**,char const*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta_get_cancellation_editor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,void*,TYPE_3__ const**,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_opt_revision_head ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 scalar_t__ svn_opt_revision_working ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_do_update3 (int /*<<< orphan*/ *,TYPE_1__ const**,void**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
bench_null_export(svn_revnum_t *result_rev,
                  const char *from_path_or_url,
                  svn_opt_revision_t *peg_revision,
                  svn_opt_revision_t *revision,
                  svn_depth_t depth,
                  void *baton,
                  svn_client_ctx_t *ctx,
                  svn_boolean_t quiet,
                  apr_pool_t *pool)
{
  svn_revnum_t edit_revision = SVN_INVALID_REVNUM;
  svn_boolean_t from_is_url = svn_path_is_url(from_path_or_url);

  SVN_ERR_ASSERT(peg_revision != NULL);
  SVN_ERR_ASSERT(revision != NULL);

  if (peg_revision->kind == svn_opt_revision_unspecified)
    peg_revision->kind = svn_path_is_url(from_path_or_url)
                       ? svn_opt_revision_head
                       : svn_opt_revision_working;

  if (revision->kind == svn_opt_revision_unspecified)
    revision = peg_revision;

  if (from_is_url || ! SVN_CLIENT__REVKIND_IS_LOCAL_TO_WC(revision->kind))
    {
      svn_client__pathrev_t *loc;
      svn_ra_session_t *ra_session;
      svn_node_kind_t kind;
      edit_baton_t *eb = baton;

      /* Get the RA connection. */
      SVN_ERR(svn_client__ra_session_from_path2(&ra_session, &loc,
                                                from_path_or_url, NULL,
                                                peg_revision,
                                                revision, ctx, pool));

      SVN_ERR(svn_ra_check_path(ra_session, "", loc->rev, &kind, pool));

      if (kind == svn_node_file)
        {
          apr_hash_t *props;

          /* Since we don't use the editor, we must count "manually". */
          svn_stream_t *stream = svn_stream_create(eb, pool);
          svn_stream_set_write(stream, file_write_handler);
          eb->file_count++;

          /* Since you cannot actually root an editor at a file, we
           * manually drive a few functions of our editor. */

          /* Step outside the editor-likeness for a moment, to actually talk
           * to the repository. */
          /* ### note: the stream will not be closed */
          SVN_ERR(svn_ra_get_file(ra_session, "", loc->rev,
                                  stream, NULL, &props, pool));
        }
      else if (kind == svn_node_dir)
        {
          void *edit_baton = NULL;
          const svn_delta_editor_t *export_editor = NULL;
          const svn_ra_reporter3_t *reporter;
          void *report_baton;

          svn_delta_editor_t *editor = svn_delta_default_editor(pool);

          editor->set_target_revision = set_target_revision;
          editor->open_root = open_root;
          editor->add_directory = add_directory;
          editor->add_file = add_file;
          editor->apply_textdelta = apply_textdelta;
          editor->close_file = close_file;
          editor->change_file_prop = change_file_prop;
          editor->change_dir_prop = change_dir_prop;

          /* for ra_svn, we don't need an editior in quiet mode */
          if (!quiet || strncmp(loc->repos_root_url, "svn:", 4))
            SVN_ERR(svn_delta_get_cancellation_editor(ctx->cancel_func,
                                                      ctx->cancel_baton,
                                                      editor,
                                                      baton,
                                                      &export_editor,
                                                      &edit_baton,
                                                      pool));

          /* Manufacture a basic 'report' to the update reporter. */
          SVN_ERR(svn_ra_do_update3(ra_session,
                                    &reporter, &report_baton,
                                    loc->rev,
                                    "", /* no sub-target */
                                    depth,
                                    FALSE, /* don't want copyfrom-args */
                                    FALSE, /* don't want ignore_ancestry */
                                    export_editor, edit_baton,
                                    pool, pool));

          SVN_ERR(reporter->set_path(report_baton, "", loc->rev,
                                     /* Depth is irrelevant, as we're
                                        passing start_empty=TRUE anyway. */
                                     svn_depth_infinity,
                                     TRUE, /* "help, my dir is empty!" */
                                     NULL, pool));

          SVN_ERR(reporter->finish_report(report_baton, pool));

          /* We don't receive the "add directory" callback for the starting
           * node. */
          eb->dir_count++;
        }
      else if (kind == svn_node_none)
        {
          return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                                   _("URL '%s' doesn't exist"),
                                   from_path_or_url);
        }
      /* kind == svn_node_unknown not handled */
    }


  if (result_rev)
    *result_rev = edit_revision;

  return SVN_NO_ERROR;
}