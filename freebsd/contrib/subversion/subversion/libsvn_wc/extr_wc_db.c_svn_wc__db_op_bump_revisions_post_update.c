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
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bump_revisions_post_update (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_op_bump_revisions_post_update(svn_wc__db_t *db,
                                         const char *local_abspath,
                                         svn_depth_t depth,
                                         const char *new_repos_relpath,
                                         const char *new_repos_root_url,
                                         const char *new_repos_uuid,
                                         svn_revnum_t new_revision,
                                         apr_hash_t *exclude_relpaths,
                                         apr_hash_t *wcroot_iprops,
                                         svn_boolean_t empty_update,
                                         svn_wc_notify_func2_t notify_func,
                                         void *notify_baton,
                                         apr_pool_t *scratch_pool)
{
  const char *local_relpath;
  svn_wc__db_wcroot_t *wcroot;

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              local_abspath, scratch_pool, scratch_pool));

  VERIFY_USABLE_WCROOT(wcroot);

  if (svn_hash_gets(exclude_relpaths, local_relpath))
    return SVN_NO_ERROR;

  if (depth == svn_depth_unknown)
    depth = svn_depth_infinity;

  SVN_WC__DB_WITH_TXN(
    bump_revisions_post_update(wcroot, local_relpath, db,
                               depth, new_repos_relpath, new_repos_root_url,
                               new_repos_uuid, new_revision,
                               exclude_relpaths, wcroot_iprops, empty_update,
                               notify_func, notify_baton, scratch_pool),
    wcroot);

  return SVN_NO_ERROR;
}