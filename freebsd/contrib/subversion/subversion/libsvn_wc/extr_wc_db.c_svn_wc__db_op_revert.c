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
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct with_triggers_baton_t {int /*<<< orphan*/  cb_func; struct revert_baton_t* cb_baton; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct revert_baton_t {int /*<<< orphan*/  clear_changelists; int /*<<< orphan*/ * db; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_CREATE_REVERT_LIST ; 
 int /*<<< orphan*/  STMT_DROP_REVERT_LIST_TRIGGERS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  flush_entries (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_revert_recursive_txn ; 
 int /*<<< orphan*/  op_revert_txn ; 
#define  svn_depth_empty 129 
#define  svn_depth_infinity 128 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  with_triggers (struct with_triggers_baton_t*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_op_revert(svn_wc__db_t *db,
                     const char *local_abspath,
                     svn_depth_t depth,
                     svn_boolean_t clear_changelists,
                     apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  struct revert_baton_t rvb;
  struct with_triggers_baton_t wtb = { STMT_CREATE_REVERT_LIST,
                                       STMT_DROP_REVERT_LIST_TRIGGERS,
                                       NULL, NULL};

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  rvb.db = db;
  rvb.clear_changelists = clear_changelists;
  wtb.cb_baton = &rvb;

  switch (depth)
    {
    case svn_depth_empty:
      wtb.cb_func = op_revert_txn;
      break;
    case svn_depth_infinity:
      wtb.cb_func = op_revert_recursive_txn;
      break;
    default:
      return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                               _("Unsupported depth for revert of '%s'"),
                               svn_dirent_local_style(local_abspath,
                                                      scratch_pool));
    }

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath,
                              db, local_abspath, scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  SVN_WC__DB_WITH_TXN(with_triggers(&wtb, wcroot, local_relpath, scratch_pool),
                      wcroot);

  SVN_ERR(flush_entries(wcroot, local_abspath, depth, scratch_pool));

  return SVN_NO_ERROR;
}