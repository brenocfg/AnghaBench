#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* revision; void* old_revision; void* prop_state; void* content_state; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,TYPE_1__*,int /*<<< orphan*/ *) ;
typedef  void* svn_wc_notify_action_t ;
struct TYPE_8__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_3__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_FINALIZE_UPDATE_MOVE ; 
 int /*<<< orphan*/  STMT_SELECT_UPDATE_MOVE_LIST ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  kind_map_none ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 void* svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_update_move_list_notify(svn_wc__db_wcroot_t *wcroot,
                                   svn_revnum_t old_revision,
                                   svn_revnum_t new_revision,
                                   svn_wc_notify_func2_t notify_func,
                                   void *notify_baton,
                                   apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;

  if (notify_func)
    {
      apr_pool_t *iterpool;
      svn_boolean_t have_row;

      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_UPDATE_MOVE_LIST));
      SVN_ERR(svn_sqlite__step(&have_row, stmt));

      iterpool = svn_pool_create(scratch_pool);
      while (have_row)
        {
          const char *local_relpath;
          svn_wc_notify_action_t action;
          svn_wc_notify_t *notify;

          svn_pool_clear(iterpool);

          local_relpath = svn_sqlite__column_text(stmt, 0, NULL);
          action = svn_sqlite__column_int(stmt, 1);
          notify = svn_wc_create_notify(svn_dirent_join(wcroot->abspath,
                                                        local_relpath,
                                                        iterpool),
                                        action, iterpool);
          notify->kind = svn_sqlite__column_token(stmt, 2, kind_map_none);
          notify->content_state = svn_sqlite__column_int(stmt, 3);
          notify->prop_state = svn_sqlite__column_int(stmt, 4);
          notify->old_revision = old_revision;
          notify->revision = new_revision;
          notify_func(notify_baton, notify, scratch_pool);

          SVN_ERR(svn_sqlite__step(&have_row, stmt));
        }
      svn_pool_destroy(iterpool);
      SVN_ERR(svn_sqlite__reset(stmt));
    }

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_FINALIZE_UPDATE_MOVE));
  SVN_ERR(svn_sqlite__step_done(stmt));

  return SVN_NO_ERROR;
}