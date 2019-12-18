#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  int svn_boolean_t ;
struct TYPE_10__ {char const* local_abspath; scalar_t__ kind_on_disk; char const* move_target_abspath; int /*<<< orphan*/  executable; scalar_t__ added; TYPE_1__* content; int /*<<< orphan*/  patched_path; scalar_t__ git_symlink_format; scalar_t__ is_special; void* skipped; void* obstructed; scalar_t__ deleted; } ;
typedef  TYPE_3__ patch_target_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_8__ {scalar_t__ eol_style; int /*<<< orphan*/  keywords; int /*<<< orphan*/  eol_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  create_missing_parents (TYPE_3__*,char const*,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_executable (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_subst_copy_and_translate4 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_create_specialfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_subst_eol_style_fixed ; 
 scalar_t__ svn_subst_eol_style_native ; 
 int /*<<< orphan*/  svn_wc__move2 (int /*<<< orphan*/ ,char const*,char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_add_from_disk3 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_delete4 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_read_kind2 (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
install_patched_target(patch_target_t *target, const char *abs_wc_path,
                       svn_client_ctx_t *ctx, svn_boolean_t dry_run,
                       apr_array_header_t *targets_info,
                       apr_pool_t *pool)
{
  if (target->deleted)
    {
      if (! dry_run)
        {
          /* Schedule the target for deletion.  Suppress
           * notification, we'll do it manually in a minute
           * because we also need to notify during dry-run.
           * Also suppress cancellation, because we'd rather
           * notify about what we did before aborting. */
          SVN_ERR(svn_wc_delete4(ctx->wc_ctx, target->local_abspath,
                                 FALSE /* keep_local */, FALSE,
                                 ctx->cancel_func, ctx->cancel_baton,
                                 NULL, NULL /* notify */,
                                 pool));
        }
    }
  else
    {
      svn_node_kind_t parent_db_kind;
      if (target->added)
        {
          const char *parent_abspath;

          parent_abspath = svn_dirent_dirname(target->local_abspath,
                                              pool);
          /* If the target's parent directory does not yet exist
           * we need to create it before we can copy the patched
           * result in place. */
          SVN_ERR(svn_wc_read_kind2(&parent_db_kind, ctx->wc_ctx,
                                    parent_abspath, FALSE, FALSE, pool));

          /* We can't add targets under nodes scheduled for delete, so add
             a new directory if needed. */
          if (parent_db_kind == svn_node_dir
              || parent_db_kind == svn_node_file)
            {
              if (parent_db_kind != svn_node_dir)
                target->skipped = TRUE;
              else
                {
                  svn_node_kind_t disk_kind;

                  SVN_ERR(svn_io_check_path(parent_abspath, &disk_kind, pool));
                  if (disk_kind != svn_node_dir)
                    target->skipped = TRUE;
                }
            }
          else
            SVN_ERR(create_missing_parents(target, abs_wc_path, ctx,
                                           dry_run, targets_info, pool));

        }
      else
        {
          svn_node_kind_t wc_kind;

          /* The target should exist */
          SVN_ERR(svn_wc_read_kind2(&wc_kind, ctx->wc_ctx,
                                    target->local_abspath,
                                    FALSE, FALSE, pool));

          if (target->kind_on_disk == svn_node_none
              || wc_kind != target->kind_on_disk)
            {
              target->skipped = TRUE;
              if (wc_kind != target->kind_on_disk)
                target->obstructed = TRUE;
            }
        }

      if (! dry_run && ! target->skipped)
        {
          if (target->is_special)
            {
              svn_stream_t *stream;
              svn_stream_t *patched_stream;

              SVN_ERR(svn_stream_open_readonly(&patched_stream,
                                               target->patched_path,
                                               pool, pool));
              SVN_ERR(svn_subst_create_specialfile(&stream,
                                                   target->local_abspath,
                                                   pool, pool));
              if (target->git_symlink_format)
                  SVN_ERR(svn_stream_puts(stream, "link "));
              SVN_ERR(svn_stream_copy3(patched_stream, stream,
                                       ctx->cancel_func, ctx->cancel_baton,
                                       pool));
            }
          else
            {
              svn_boolean_t repair_eol;

              /* Copy the patched file on top of the target file.
               * Always expand keywords in the patched file, but repair EOL
               * only if svn:eol-style dictates a particular style. */
              repair_eol = (target->content->eol_style ==
                              svn_subst_eol_style_fixed ||
                            target->content->eol_style ==
                              svn_subst_eol_style_native);

              SVN_ERR(svn_subst_copy_and_translate4(
                        target->patched_path,
                        target->move_target_abspath
                          ? target->move_target_abspath
                          : target->local_abspath,
                        target->content->eol_str, repair_eol,
                        target->content->keywords,
                        TRUE /* expand */, FALSE /* special */,
                        ctx->cancel_func, ctx->cancel_baton, pool));
            }

          if (target->added)
            {
              /* The target file didn't exist previously,
               * so add it to version control.
               * Suppress notification, we'll do that later (and also
               * during dry-run). Don't allow cancellation because
               * we'd rather notify about what we did before aborting. */
              SVN_ERR(svn_wc_add_from_disk3(ctx->wc_ctx, target->local_abspath,
                                            NULL /*props*/,
                                            FALSE /* skip checks */,
                                            NULL, NULL, pool));
            }

          /* Restore the target's executable bit if necessary. */
          SVN_ERR(svn_io_set_file_executable(target->move_target_abspath
                                               ? target->move_target_abspath
                                               : target->local_abspath,
                                             target->executable,
                                             FALSE, pool));

          if (target->move_target_abspath)
            {
              /* ### Copying the patched content to the move target location,
               * performing the move in meta-data, and removing the file at
               * the move source should be one atomic operation. */

              /* ### Create missing parents. */

              /* Perform the move in meta-data. */
              SVN_ERR(svn_wc__move2(ctx->wc_ctx,
                                    target->local_abspath,
                                    target->move_target_abspath,
                                    TRUE, /* metadata_only */
                                    FALSE, /* allow_mixed_revisions */
                                    ctx->cancel_func, ctx->cancel_baton,
                                    NULL, NULL,
                                    pool));

              /* Delete the patch target's old location from disk. */
              SVN_ERR(svn_io_remove_file2(target->local_abspath, FALSE, pool));
            }
        }
    }

  return SVN_NO_ERROR;
}