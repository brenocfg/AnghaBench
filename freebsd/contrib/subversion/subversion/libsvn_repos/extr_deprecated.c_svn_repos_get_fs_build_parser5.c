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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_repos_parse_fns3_t ;
typedef  int /*<<< orphan*/  svn_repos_notify_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  enum svn_repos_load_uuid { ____Placeholder_svn_repos_load_uuid } svn_repos_load_uuid ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_repos_get_fs_build_parser6 (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_get_fs_build_parser5(const svn_repos_parse_fns3_t **parser,
                               void **parse_baton,
                               svn_repos_t *repos,
                               svn_revnum_t start_rev,
                               svn_revnum_t end_rev,
                               svn_boolean_t use_history,
                               svn_boolean_t validate_props,
                               enum svn_repos_load_uuid uuid_action,
                               const char *parent_dir,
                               svn_boolean_t use_pre_commit_hook,
                               svn_boolean_t use_post_commit_hook,
                               svn_boolean_t ignore_dates,
                               svn_repos_notify_func_t notify_func,
                               void *notify_baton,
                               apr_pool_t *pool)
{
  SVN_ERR(svn_repos_get_fs_build_parser6(parser, parse_baton,
                                         repos,
                                         start_rev, end_rev,
                                         use_history,
                                         validate_props,
                                         uuid_action,
                                         parent_dir,
                                         use_pre_commit_hook,
                                         use_post_commit_hook,
                                         ignore_dates,
                                         FALSE /* normalize_props */,
                                         notify_func,
                                         notify_baton,
                                         pool));
  return SVN_NO_ERROR;
}