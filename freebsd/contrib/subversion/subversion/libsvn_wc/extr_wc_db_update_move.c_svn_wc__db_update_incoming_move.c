#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_operation_t ;
struct TYPE_12__ {int /*<<< orphan*/  revision; void* prop_state; void* content_state; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,TYPE_1__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_wc_conflict_reason_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_action_t ;
struct TYPE_13__ {int /*<<< orphan*/  abspath; } ;
typedef  TYPE_3__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_node_none ; 
 int /*<<< orphan*/  svn_wc__db_update_move_list_notify (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*,TYPE_1__*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_3__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_update_completed ; 
 int /*<<< orphan*/  update_incoming_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_update_incoming_move(svn_wc__db_t *db,
                                const char *local_abspath,
                                const char *dest_abspath,
                                svn_wc_operation_t operation,
                                svn_wc_conflict_action_t action,
                                svn_wc_conflict_reason_t reason,
                                svn_cancel_func_t cancel_func,
                                void *cancel_baton,
                                svn_wc_notify_func2_t notify_func,
                                void *notify_baton,
                                apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  svn_revnum_t old_rev, new_rev;
  const char *local_relpath;
  const char *dest_relpath;

  /* ### Check for mixed-rev src or dst? */

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath,
                                                db, local_abspath,
                                                scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  dest_relpath
    = svn_dirent_skip_ancestor(wcroot->abspath, dest_abspath);

  SVN_WC__DB_WITH_TXN(update_incoming_move(&old_rev, &new_rev, db, wcroot,
                                           local_relpath, dest_relpath,
                                           operation, action, reason,
                                           cancel_func, cancel_baton,
                                           scratch_pool),
                      wcroot);

  /* Send all queued up notifications. */
  SVN_ERR(svn_wc__db_update_move_list_notify(wcroot, old_rev, new_rev,
                                             notify_func, notify_baton,
                                             scratch_pool));
  if (notify_func)
    {
      svn_wc_notify_t *notify;

      notify = svn_wc_create_notify(svn_dirent_join(wcroot->abspath,
                                                    local_relpath,
                                                    scratch_pool),
                                    svn_wc_notify_update_completed,
                                    scratch_pool);
      notify->kind = svn_node_none;
      notify->content_state = svn_wc_notify_state_inapplicable;
      notify->prop_state = svn_wc_notify_state_inapplicable;
      notify->revision = new_rev;
      notify_func(notify_baton, notify, scratch_pool);
    }


  return SVN_NO_ERROR;
}