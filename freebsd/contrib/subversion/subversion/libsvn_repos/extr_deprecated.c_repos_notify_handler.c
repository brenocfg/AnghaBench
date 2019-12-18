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
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_3__ {int action; int /*<<< orphan*/  old_revision; int /*<<< orphan*/  path; int /*<<< orphan*/  node_action; int /*<<< orphan*/  new_revision; int /*<<< orphan*/  revision; int /*<<< orphan*/  warning_str; } ;
typedef  TYPE_1__ svn_repos_notify_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
#define  svn_node_action_add 140 
#define  svn_node_action_change 139 
#define  svn_node_action_delete 138 
#define  svn_node_action_replace 137 
#define  svn_repos_notify_dump_rev_end 136 
#define  svn_repos_notify_load_copied_node 135 
#define  svn_repos_notify_load_node_done 134 
#define  svn_repos_notify_load_node_start 133 
#define  svn_repos_notify_load_normalized_mergeinfo 132 
#define  svn_repos_notify_load_txn_committed 131 
#define  svn_repos_notify_load_txn_start 130 
#define  svn_repos_notify_verify_rev_end 129 
#define  svn_repos_notify_warning 128 
 int /*<<< orphan*/  svn_stream_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static void
repos_notify_handler(void *baton,
                     const svn_repos_notify_t *notify,
                     apr_pool_t *scratch_pool)
{
  svn_stream_t *feedback_stream = baton;
  apr_size_t len;

  switch (notify->action)
  {
    case svn_repos_notify_warning:
      svn_error_clear(svn_stream_puts(feedback_stream, notify->warning_str));
      return;

    case svn_repos_notify_dump_rev_end:
      svn_error_clear(svn_stream_printf(feedback_stream, scratch_pool,
                                        _("* Dumped revision %ld.\n"),
                                        notify->revision));
      return;

    case svn_repos_notify_verify_rev_end:
      svn_error_clear(svn_stream_printf(feedback_stream, scratch_pool,
                                        _("* Verified revision %ld.\n"),
                                        notify->revision));
      return;

    case svn_repos_notify_load_txn_committed:
      if (notify->old_revision == SVN_INVALID_REVNUM)
        {
          svn_error_clear(svn_stream_printf(feedback_stream, scratch_pool,
                            _("\n------- Committed revision %ld >>>\n\n"),
                            notify->new_revision));
        }
      else
        {
          svn_error_clear(svn_stream_printf(feedback_stream, scratch_pool,
                            _("\n------- Committed new rev %ld"
                              " (loaded from original rev %ld"
                              ") >>>\n\n"), notify->new_revision,
                              notify->old_revision));
        }
      return;

    case svn_repos_notify_load_node_start:
      {
        switch (notify->node_action)
        {
          case svn_node_action_change:
            svn_error_clear(svn_stream_printf(feedback_stream, scratch_pool,
                                  _("     * editing path : %s ..."),
                                  notify->path));
            break;

          case svn_node_action_delete:
            svn_error_clear(svn_stream_printf(feedback_stream, scratch_pool,
                                  _("     * deleting path : %s ..."),
                                  notify->path));
            break;

          case svn_node_action_add:
            svn_error_clear(svn_stream_printf(feedback_stream, scratch_pool,
                                  _("     * adding path : %s ..."),
                                  notify->path));
            break;

          case svn_node_action_replace:
            svn_error_clear(svn_stream_printf(feedback_stream, scratch_pool,
                                  _("     * replacing path : %s ..."),
                                  notify->path));
            break;

        }
      }
      return;

    case svn_repos_notify_load_node_done:
      len = 7;
      svn_error_clear(svn_stream_write(feedback_stream, _(" done.\n"), &len));
      return;

    case svn_repos_notify_load_copied_node:
      len = 9;
      svn_error_clear(svn_stream_write(feedback_stream, "COPIED...", &len));
      return;

    case svn_repos_notify_load_txn_start:
      svn_error_clear(svn_stream_printf(feedback_stream, scratch_pool,
                                _("<<< Started new transaction, based on "
                                  "original revision %ld\n"),
                                notify->old_revision));
      return;

    case svn_repos_notify_load_normalized_mergeinfo:
      svn_error_clear(svn_stream_printf(feedback_stream, scratch_pool,
                                _(" removing '\\r' from %s ..."),
                                SVN_PROP_MERGEINFO));
      return;

    default:
      return;
  }
}