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
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_REPOS_BAD_ARGS ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ svn_depth_exclude ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_path_info (void*,char const*,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_link_path3(void *baton, const char *path, const char *link_path,
                     svn_revnum_t rev, svn_depth_t depth,
                     svn_boolean_t start_empty,
                     const char *lock_token, apr_pool_t *pool)
{
  if (depth == svn_depth_exclude)
    return svn_error_create(SVN_ERR_REPOS_BAD_ARGS, NULL,
                            _("Depth 'exclude' not supported for link"));

  return svn_error_trace(
            write_path_info(baton, path, link_path, rev, depth,
                            start_empty, lock_token, pool));
}