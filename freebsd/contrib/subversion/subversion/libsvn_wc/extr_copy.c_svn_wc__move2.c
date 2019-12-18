#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * svn_wc_notify_func2_t ;
struct TYPE_4__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  copy_or_move (scalar_t__*,TYPE_1__*,char const*,char const*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_all_conflict_markers (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_node_conflict_markers (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_wc__db_op_delete (int /*<<< orphan*/ *,char const*,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__write_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__move2(svn_wc_context_t *wc_ctx,
              const char *src_abspath,
              const char *dst_abspath,
              svn_boolean_t metadata_only,
              svn_boolean_t allow_mixed_revisions,
              svn_cancel_func_t cancel_func,
              void *cancel_baton,
              svn_wc_notify_func2_t notify_func,
              void *notify_baton,
              apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db = wc_ctx->db;
  svn_boolean_t record_on_delete = TRUE;
  svn_node_kind_t kind;
  svn_boolean_t conflicted;

  /* Verify that we have the required write locks. */
  SVN_ERR(svn_wc__write_check(wc_ctx->db,
                              svn_dirent_dirname(src_abspath, scratch_pool),
                              scratch_pool));
  SVN_ERR(svn_wc__write_check(wc_ctx->db,
                              svn_dirent_dirname(dst_abspath, scratch_pool),
                              scratch_pool));

  SVN_ERR(copy_or_move(&record_on_delete,
                       wc_ctx, src_abspath, dst_abspath,
                       TRUE /* metadata_only */,
                       TRUE /* is_move */,
                       allow_mixed_revisions,
                       cancel_func, cancel_baton,
                       notify_func, notify_baton,
                       scratch_pool));

  /* An interrupt at this point will leave the new copy marked as
     moved-here but the source has not yet been deleted or marked as
     moved-to. */

  /* Should we be using a workqueue for this move?  It's not clear.
     What should happen if the copy above is interrupted?  The user
     may want to abort the move and a workqueue might interfere with
     that.

     BH: On Windows it is not unlikely to encounter an access denied on
     this line. Installing the move in the workqueue via the copy_or_move
     might make it hard to recover from that situation, while the DB
     is still in a valid state. So be careful when switching this over
     to the workqueue. */
  if (!metadata_only)
    {
      svn_error_t *err;

      err = svn_error_trace(svn_io_file_rename2(src_abspath, dst_abspath,
                                                FALSE, scratch_pool));

      /* Let's try if we can keep wc.db consistent even when the move
         fails. Deleting the target is a wc.db only operation, while
         going forward (delaying the error) would try to change
         conflict markers, which might also fail. */
      if (err)
        return svn_error_trace(
          svn_error_compose_create(
              err,
              svn_wc__db_op_delete(wc_ctx->db, dst_abspath, NULL, TRUE,
                                   NULL, NULL, cancel_func, cancel_baton,
                                   NULL, NULL,
                                   scratch_pool)));
    }

  SVN_ERR(svn_wc__db_read_info(NULL, &kind, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL,
                               &conflicted, NULL, NULL, NULL,
                               NULL, NULL, NULL,
                               db, src_abspath,
                               scratch_pool, scratch_pool));

  if (kind == svn_node_dir)
    SVN_ERR(remove_all_conflict_markers(db, src_abspath, dst_abspath,
                                        cancel_func, cancel_baton,
                                        scratch_pool));

  if (conflicted)
    {
      /* When we moved a directory, we moved the conflict markers
         with the target... if we moved a file we only moved the
         file itself and the markers are still in the old location */
      SVN_ERR(remove_node_conflict_markers(db, src_abspath,
                                           (kind == svn_node_dir)
                                             ? dst_abspath
                                             : src_abspath,
                                           scratch_pool));
    }

  SVN_ERR(svn_wc__db_op_delete(db, src_abspath,
                               record_on_delete ? dst_abspath : NULL,
                               TRUE /* delete_dir_externals */,
                               NULL /* conflict */, NULL /* work_items */,
                               cancel_func, cancel_baton,
                               notify_func, notify_baton,
                               scratch_pool));

  return SVN_NO_ERROR;
}