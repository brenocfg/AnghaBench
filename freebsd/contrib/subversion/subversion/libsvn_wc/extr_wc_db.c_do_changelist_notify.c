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
struct TYPE_7__ {void* changelist_name; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,TYPE_1__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_wc_notify_action_t ;
struct TYPE_8__ {int /*<<< orphan*/  abspath; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_3__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/ * (* svn_cancel_func_t ) (void*) ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_CHANGELIST_LIST ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 void* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
do_changelist_notify(void *baton,
                     svn_wc__db_wcroot_t *wcroot,
                     svn_cancel_func_t cancel_func,
                     void *cancel_baton,
                     svn_wc_notify_func2_t notify_func,
                     void *notify_baton,
                     apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  apr_pool_t *iterpool;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_CHANGELIST_LIST));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  iterpool = svn_pool_create(scratch_pool);
  while (have_row)
    {
      /* ### wc_id is column 0. use it one day...  */
      const char *notify_relpath = svn_sqlite__column_text(stmt, 1, NULL);
      svn_wc_notify_action_t action = svn_sqlite__column_int(stmt, 2);
      svn_wc_notify_t *notify;
      const char *notify_abspath;

      svn_pool_clear(iterpool);

      if (cancel_func)
        {
          svn_error_t *err = cancel_func(cancel_baton);

          if (err)
            return svn_error_trace(svn_error_compose_create(
                                                    err,
                                                    svn_sqlite__reset(stmt)));
        }

      notify_abspath = svn_dirent_join(wcroot->abspath, notify_relpath,
                                       iterpool);
      notify = svn_wc_create_notify(notify_abspath, action, iterpool);
      notify->changelist_name = svn_sqlite__column_text(stmt, 3, NULL);
      notify_func(notify_baton, notify, iterpool);

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }
  svn_pool_destroy(iterpool);

  return svn_error_trace(svn_sqlite__reset(stmt));
}