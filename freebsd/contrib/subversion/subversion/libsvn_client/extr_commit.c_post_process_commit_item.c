#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_committed_queue_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int state_flags; scalar_t__ kind; int /*<<< orphan*/  incoming_prop_changes; int /*<<< orphan*/  path; scalar_t__ copyfrom_url; } ;
typedef  TYPE_1__ svn_client_commit_item3_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int SVN_CLIENT_COMMIT_ITEM_ADD ; 
 int SVN_CLIENT_COMMIT_ITEM_DELETE ; 
 int SVN_CLIENT_COMMIT_ITEM_LOCK_TOKEN ; 
 int SVN_CLIENT_COMMIT_ITEM_PROP_MODS ; 
 int SVN_CLIENT_COMMIT_ITEM_TEXT_MODS ; 
 int TRUE ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_wc_queue_committed4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
post_process_commit_item(svn_wc_committed_queue_t *queue,
                         const svn_client_commit_item3_t *item,
                         svn_wc_context_t *wc_ctx,
                         svn_boolean_t keep_changelists,
                         svn_boolean_t keep_locks,
                         svn_boolean_t commit_as_operations,
                         const svn_checksum_t *sha1_checksum,
                         apr_pool_t *scratch_pool)
{
  svn_boolean_t loop_recurse = FALSE;
  svn_boolean_t remove_lock;

  if (! commit_as_operations
      && (item->state_flags & SVN_CLIENT_COMMIT_ITEM_ADD)
      && (item->kind == svn_node_dir)
      && (item->copyfrom_url))
    loop_recurse = TRUE;

  remove_lock = (! keep_locks && (item->state_flags
                                       & (SVN_CLIENT_COMMIT_ITEM_LOCK_TOKEN
                                          | SVN_CLIENT_COMMIT_ITEM_ADD
                                          | SVN_CLIENT_COMMIT_ITEM_DELETE)));

  /* When the node was deleted (or replaced), we need to always remove the
     locks, as they're invalidated on the server. We cannot honor the
     SVN_CLIENT_COMMIT_ITEM_LOCK_TOKEN flag here because it does not tell
     us whether we have locked children. */
  if (item->state_flags & SVN_CLIENT_COMMIT_ITEM_DELETE)
    remove_lock = TRUE;

  return svn_error_trace(
         svn_wc_queue_committed4(queue, wc_ctx, item->path,
                                 loop_recurse,
                                 0 != (item->state_flags &
                                       (SVN_CLIENT_COMMIT_ITEM_ADD
                                        | SVN_CLIENT_COMMIT_ITEM_DELETE
                                        | SVN_CLIENT_COMMIT_ITEM_TEXT_MODS
                                        | SVN_CLIENT_COMMIT_ITEM_PROP_MODS)),
                                 item->incoming_prop_changes,
                                 remove_lock, !keep_changelists,
                                 sha1_checksum, scratch_pool));
}