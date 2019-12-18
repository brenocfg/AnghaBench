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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_8__ {void* subtractive_merge; void* has_children; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_repos_log_entry_t ;
typedef  scalar_t__ svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  void* svn_boolean_t ;
typedef  int /*<<< orphan*/  svn_bit_array__t ;
struct TYPE_9__ {int /*<<< orphan*/  revision_receiver_baton; int /*<<< orphan*/  (* revision_receiver ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;TYPE_3__* path_change_receiver_baton; int /*<<< orphan*/  path_change_receiver; } ;
typedef  TYPE_2__ log_callbacks_t ;
struct TYPE_10__ {scalar_t__ found_rev_of_interest; struct TYPE_10__* inner_baton; int /*<<< orphan*/  inner; scalar_t__ log_target_history_as_mergeinfo; int /*<<< orphan*/  rev; } ;
typedef  TYPE_3__ interesting_merge_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 scalar_t__ apr_hash_count (scalar_t__) ; 
 int /*<<< orphan*/  fill_log_entry (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interesting_merge ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_bit_array__get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_bit_array__set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
send_log(svn_revnum_t rev,
         svn_fs_t *fs,
         svn_mergeinfo_t log_target_history_as_mergeinfo,
         svn_bit_array__t *nested_merges,
         svn_boolean_t subtractive_merge,
         svn_boolean_t handling_merged_revision,
         const apr_array_header_t *revprops,
         svn_boolean_t has_children,
         const log_callbacks_t *callbacks,
         apr_pool_t *pool)
{
  svn_repos_log_entry_t log_entry = { 0 };
  log_callbacks_t my_callbacks = *callbacks;

  interesting_merge_baton_t baton;

  /* Is REV a merged revision that is already part of
     LOG_TARGET_HISTORY_AS_MERGEINFO?  If so then there is no
     need to send it, since it already was (or will be) sent.

     Use our callback to snoop through the changes. */
  if (handling_merged_revision
      && log_target_history_as_mergeinfo
      && apr_hash_count(log_target_history_as_mergeinfo))
    {
      baton.found_rev_of_interest = FALSE;
      baton.rev = rev;
      baton.log_target_history_as_mergeinfo = log_target_history_as_mergeinfo;
      baton.inner = callbacks->path_change_receiver;
      baton.inner_baton = callbacks->path_change_receiver_baton;

      my_callbacks.path_change_receiver = interesting_merge;
      my_callbacks.path_change_receiver_baton = &baton;
      callbacks = &my_callbacks;
    }
  else
    {
      baton.found_rev_of_interest = TRUE;
    }

  SVN_ERR(fill_log_entry(&log_entry, rev, fs, revprops, callbacks, pool));
  log_entry.has_children = has_children;
  log_entry.subtractive_merge = subtractive_merge;

  /* Send the entry to the receiver, unless it is a redundant merged
     revision. */
  if (baton.found_rev_of_interest)
    {
      apr_pool_t *scratch_pool;

      /* Is REV a merged revision we've already sent? */
      if (nested_merges && handling_merged_revision)
        {
          if (svn_bit_array__get(nested_merges, rev))
            {
              /* We already sent REV. */
              return SVN_NO_ERROR;
            }
          else
            {
              /* NESTED_REVS needs to last across all the send_log, do_logs,
                 handle_merged_revisions() recursions, so use the pool it
                 was created in at the top of the recursion. */
              svn_bit_array__set(nested_merges, rev, TRUE);
            }
        }

      /* Pass a scratch pool to ensure no temporary state stored
         by the receiver callback persists. */
      scratch_pool = svn_pool_create(pool);
      SVN_ERR(callbacks->revision_receiver(callbacks->revision_receiver_baton,
                                           &log_entry, scratch_pool));
      svn_pool_destroy(scratch_pool);
    }

  return SVN_NO_ERROR;
}