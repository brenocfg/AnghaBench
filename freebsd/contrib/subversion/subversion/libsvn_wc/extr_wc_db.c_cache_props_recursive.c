#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ pristine; int /*<<< orphan*/  changelists; int /*<<< orphan*/  depth; } ;
typedef  TYPE_2__ cache_props_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int STMT_CACHE_TARGET_PRISTINE_PROPS ; 
 int STMT_CACHE_TARGET_PROPS ; 
 int /*<<< orphan*/  STMT_CREATE_TARGET_PROP_CACHE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  populate_targets_tree (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__exec_statements (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
cache_props_recursive(void *cb_baton,
                      svn_wc__db_wcroot_t *wcroot,
                      const char *local_relpath,
                      apr_pool_t *scratch_pool)
{
  cache_props_baton_t *baton = cb_baton;
  svn_sqlite__stmt_t *stmt;
  int stmt_idx;

  SVN_ERR(populate_targets_tree(wcroot, local_relpath, baton->depth,
                                baton->changelists, scratch_pool));

  SVN_ERR(svn_sqlite__exec_statements(wcroot->sdb,
                                      STMT_CREATE_TARGET_PROP_CACHE));

  if (baton->pristine)
    stmt_idx = STMT_CACHE_TARGET_PRISTINE_PROPS;
  else
    stmt_idx = STMT_CACHE_TARGET_PROPS;

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb, stmt_idx));
  SVN_ERR(svn_sqlite__bind_int64(stmt, 1, wcroot->wc_id));
  SVN_ERR(svn_sqlite__step_done(stmt));

  return SVN_NO_ERROR;
}