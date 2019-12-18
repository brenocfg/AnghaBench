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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_UPGRADE_30_SET_CONFLICT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn_sqlite__column_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__upgrade_conflict_skel_from_raw (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
bump_30_upgrade_one_conflict(svn_wc__db_t *wc_db,
                             const char *wcroot_abspath,
                             svn_sqlite__stmt_t *stmt,
                             svn_sqlite__db_t *sdb,
                             apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt_store;
  svn_stringbuf_t *skel_data;
  svn_skel_t *conflict_data;
  apr_int64_t wc_id = svn_sqlite__column_int64(stmt, 0);
  const char *local_relpath = svn_sqlite__column_text(stmt, 1, NULL);
  const char *conflict_old = svn_sqlite__column_text(stmt, 2, NULL);
  const char *conflict_wrk = svn_sqlite__column_text(stmt, 3, NULL);
  const char *conflict_new = svn_sqlite__column_text(stmt, 4, NULL);
  const char *prop_reject = svn_sqlite__column_text(stmt, 5, NULL);
  apr_size_t tree_conflict_size;
  const char *tree_conflict_data = svn_sqlite__column_blob(stmt, 6,
                                           &tree_conflict_size, NULL);

  SVN_ERR(svn_wc__upgrade_conflict_skel_from_raw(&conflict_data,
                                                 wc_db, wcroot_abspath,
                                                 local_relpath,
                                                 conflict_old,
                                                 conflict_wrk,
                                                 conflict_new,
                                                 prop_reject,
                                                 tree_conflict_data,
                                                 tree_conflict_size,
                                                 scratch_pool, scratch_pool));

  SVN_ERR_ASSERT(conflict_data != NULL);

  skel_data = svn_skel__unparse(conflict_data, scratch_pool);

  SVN_ERR(svn_sqlite__get_statement(&stmt_store, sdb,
                                    STMT_UPGRADE_30_SET_CONFLICT));
  SVN_ERR(svn_sqlite__bindf(stmt_store, "isb", wc_id, local_relpath,
                            skel_data->data, skel_data->len));
  SVN_ERR(svn_sqlite__step_done(stmt_store));

  return SVN_NO_ERROR;
}