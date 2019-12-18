#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  action; void* kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,TYPE_1__*,int /*<<< orphan*/ *) ;
struct TYPE_9__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_3__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_DELETE_REVERT_LIST_RECURSIVE ; 
 int /*<<< orphan*/  STMT_SELECT_REVERT_LIST_RECURSIVE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_3__*) ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  kind_map_none ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,char const*) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_3__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_revert ; 
 int /*<<< orphan*/  svn_wc_notify_tree_conflict ; 

svn_error_t *
svn_wc__db_revert_list_notify(svn_wc_notify_func2_t notify_func,
                              void *notify_baton,
                              svn_wc__db_t *db,
                              const char *local_abspath,
                              apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath,
                              db, local_abspath, scratch_pool, iterpool));
  VERIFY_USABLE_WCROOT(wcroot);

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_REVERT_LIST_RECURSIVE));
  SVN_ERR(svn_sqlite__bindf(stmt, "s", local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  if (!have_row)
    return svn_error_trace(svn_sqlite__reset(stmt)); /* optimise for no row */
  while (have_row)
    {
      const char *notify_relpath = svn_sqlite__column_text(stmt, 0, NULL);
      svn_wc_notify_t *notify;

      svn_pool_clear(iterpool);

      notify = svn_wc_create_notify(svn_dirent_join(wcroot->abspath,
                                                    notify_relpath,
                                                    iterpool),
                                    svn_wc_notify_revert,
                                    iterpool);

      if (!svn_sqlite__column_is_null(stmt, 1))
        notify->kind = svn_sqlite__column_token(stmt, 1, kind_map);
      else
        {
          if (!svn_sqlite__column_is_null(stmt, 3))
            notify->kind = svn_sqlite__column_token(stmt, 3, kind_map_none);

          switch (svn_sqlite__column_int(stmt, 2))
            {
              case 0:
                continue;
              case 1:
                /* standard revert */
                break;
              case 2:
                notify->action = svn_wc_notify_tree_conflict;
                break;
              default:
                SVN_ERR_MALFUNCTION();
            }
        }

      notify_func(notify_baton, notify, iterpool);

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }
  SVN_ERR(svn_sqlite__reset(stmt));

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_DELETE_REVERT_LIST_RECURSIVE));
  SVN_ERR(svn_sqlite__bindf(stmt, "s", local_relpath));
  SVN_ERR(svn_sqlite__step_done(stmt));

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}