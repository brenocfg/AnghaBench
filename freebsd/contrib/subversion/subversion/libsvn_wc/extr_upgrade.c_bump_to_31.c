#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_prop_inherited_item_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_UPDATE_IPROP ; 
 int /*<<< orphan*/  STMT_UPGRADE_31_SELECT_WCROOT_NODES ; 
 int /*<<< orphan*/  STMT_UPGRADE_TO_31 ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__bind_iprops (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__exec_statements (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__step_done (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
bump_to_31(void *baton,
           svn_sqlite__db_t *sdb,
           apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt, *stmt_mark_switch_roots;
  svn_boolean_t have_row;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_array_header_t *empty_iprops = apr_array_make(
    scratch_pool, 0, sizeof(svn_prop_inherited_item_t *));
  svn_error_t *err;

  /* Run additional statements to finalize the upgrade to format 31. */
  SVN_ERR(svn_sqlite__exec_statements(sdb, STMT_UPGRADE_TO_31));

  /* Set inherited_props to an empty array for the roots of all
     switched subtrees in the WC.  This allows subsequent updates
     to recognize these roots as needing an iprops cache. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, sdb,
                                    STMT_UPGRADE_31_SELECT_WCROOT_NODES));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  err = svn_sqlite__get_statement(&stmt_mark_switch_roots, sdb,
                                  STMT_UPDATE_IPROP);
  if (err)
    return svn_error_compose_create(err, svn_sqlite__reset(stmt));

  while (have_row)
    {
      const char *switched_relpath = svn_sqlite__column_text(stmt, 1, NULL);
      apr_int64_t wc_id = svn_sqlite__column_int64(stmt, 0);

      err = svn_sqlite__bindf(stmt_mark_switch_roots, "is", wc_id,
                              switched_relpath);
      if (!err)
        err = svn_sqlite__bind_iprops(stmt_mark_switch_roots, 3,
                                      empty_iprops, iterpool);
      if (!err)
        err = svn_sqlite__step_done(stmt_mark_switch_roots);
      if (!err)
        err = svn_sqlite__step(&have_row, stmt);

      if (err)
        return svn_error_compose_create(
                err,
                svn_error_compose_create(
                  /* Reset in either order is OK. */
                  svn_sqlite__reset(stmt),
                  svn_sqlite__reset(stmt_mark_switch_roots)));
    }

  err = svn_sqlite__reset(stmt_mark_switch_roots);
  if (err)
    return svn_error_compose_create(err, svn_sqlite__reset(stmt));
  SVN_ERR(svn_sqlite__reset(stmt));

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}