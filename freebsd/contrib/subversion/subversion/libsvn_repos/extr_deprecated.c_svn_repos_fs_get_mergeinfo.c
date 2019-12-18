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
typedef  int /*<<< orphan*/  svn_repos_authz_func_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_inheritance_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  mergeinfo_receiver ; 
 int /*<<< orphan*/  svn_hash__make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs_get_mergeinfo2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_fs_get_mergeinfo(svn_mergeinfo_catalog_t *mergeinfo,
                           svn_repos_t *repos,
                           const apr_array_header_t *paths,
                           svn_revnum_t rev,
                           svn_mergeinfo_inheritance_t inherit,
                           svn_boolean_t include_descendants,
                           svn_repos_authz_func_t authz_read_func,
                           void *authz_read_baton,
                           apr_pool_t *pool)
{
  svn_mergeinfo_catalog_t result_catalog = svn_hash__make(pool);
  SVN_ERR(svn_repos_fs_get_mergeinfo2(repos, paths, rev, inherit,
                                      include_descendants,
                                      authz_read_func, authz_read_baton,
                                      mergeinfo_receiver, result_catalog,
                                      pool));
  *mergeinfo = result_catalog;

  return SVN_NO_ERROR;
}