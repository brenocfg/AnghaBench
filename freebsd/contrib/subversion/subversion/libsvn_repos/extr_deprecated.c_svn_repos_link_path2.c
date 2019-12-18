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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/ * svn_repos_link_path3 (void*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_link_path2(void *baton, const char *path, const char *link_path,
                     svn_revnum_t rev, svn_boolean_t start_empty,
                     const char *lock_token, apr_pool_t *pool)
{
  return svn_repos_link_path3(baton, path, link_path, rev, svn_depth_infinity,
                              start_empty, lock_token, pool);
}