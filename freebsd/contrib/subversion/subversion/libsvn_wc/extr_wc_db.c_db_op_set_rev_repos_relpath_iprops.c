#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_UPDATE_BASE_REPOS ; 
 int /*<<< orphan*/  STMT_UPDATE_BASE_REVISION ; 
 int /*<<< orphan*/  STMT_UPDATE_IPROP ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  flush_entries (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_iprops (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
db_op_set_rev_repos_relpath_iprops(svn_wc__db_wcroot_t *wcroot,
                                   const char *local_relpath,
                                   apr_array_header_t *iprops,
                                   svn_revnum_t rev,
                                   svn_boolean_t set_repos_relpath,
                                   const char *repos_relpath,
                                   apr_int64_t repos_id,
                                   apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;

  SVN_ERR(flush_entries(wcroot,
                        svn_dirent_join(wcroot->abspath, local_relpath,
                                        scratch_pool),
                        svn_depth_empty, scratch_pool));


  if (SVN_IS_VALID_REVNUM(rev))
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_UPDATE_BASE_REVISION));

      SVN_ERR(svn_sqlite__bindf(stmt, "isr", wcroot->wc_id, local_relpath,
                                rev));

      SVN_ERR(svn_sqlite__step_done(stmt));
    }

  if (set_repos_relpath)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_UPDATE_BASE_REPOS));

      SVN_ERR(svn_sqlite__bindf(stmt, "isis", wcroot->wc_id, local_relpath,
                                repos_id, repos_relpath));

      SVN_ERR(svn_sqlite__step_done(stmt));
    }

  /* Set or clear iprops. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_UPDATE_IPROP));
  SVN_ERR(svn_sqlite__bindf(stmt, "is",
                            wcroot->wc_id,
                            local_relpath));
  SVN_ERR(svn_sqlite__bind_iprops(stmt, 3, iprops, scratch_pool));
  SVN_ERR(svn_sqlite__step_done(stmt));

  return SVN_NO_ERROR;
}