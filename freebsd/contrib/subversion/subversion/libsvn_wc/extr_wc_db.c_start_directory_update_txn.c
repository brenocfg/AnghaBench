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
struct TYPE_3__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_UPDATE_BASE_NODE_PRESENCE_REVNUM_AND_REPOS_PATH ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_status_incomplete ; 

__attribute__((used)) static svn_error_t *
start_directory_update_txn(svn_wc__db_wcroot_t *wcroot,
                           const char *local_relpath,
                           const char *new_repos_relpath,
                           svn_revnum_t new_rev,
                           apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;

  /* Note: In the majority of calls, the repos_relpath is unchanged. */
  /* ### TODO: Maybe check if we can make repos_relpath NULL. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                    STMT_UPDATE_BASE_NODE_PRESENCE_REVNUM_AND_REPOS_PATH));

  SVN_ERR(svn_sqlite__bindf(stmt, "istrs",
                            wcroot->wc_id,
                            local_relpath,
                            presence_map, svn_wc__db_status_incomplete,
                            new_rev,
                            new_repos_relpath));
  SVN_ERR(svn_sqlite__step_done(stmt));

  return SVN_NO_ERROR;

}