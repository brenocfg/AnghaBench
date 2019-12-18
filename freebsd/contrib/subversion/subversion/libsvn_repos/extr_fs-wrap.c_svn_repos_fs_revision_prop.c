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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  scalar_t__ svn_repos_revision_access_level_t ;
typedef  int /*<<< orphan*/  svn_repos_authz_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_revision_prop2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_check_revision_access (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_repos_revision_access_none ; 
 scalar_t__ svn_repos_revision_access_partial ; 

svn_error_t *
svn_repos_fs_revision_prop(svn_string_t **value_p,
                           svn_repos_t *repos,
                           svn_revnum_t rev,
                           const char *propname,
                           svn_repos_authz_func_t authz_read_func,
                           void *authz_read_baton,
                           apr_pool_t *pool)
{
  svn_repos_revision_access_level_t readability;

  SVN_ERR(svn_repos_check_revision_access(&readability, repos, rev,
                                          authz_read_func, authz_read_baton,
                                          pool));

  if (readability == svn_repos_revision_access_none)
    {
      /* Property?  What property? */
      *value_p = NULL;
    }
  else if (readability == svn_repos_revision_access_partial)
    {
      /* Only svn:author and svn:date are fetchable. */
      if ((strcmp(propname, SVN_PROP_REVISION_AUTHOR) != 0)
          && (strcmp(propname, SVN_PROP_REVISION_DATE) != 0))
        *value_p = NULL;

      else
        SVN_ERR(svn_fs_revision_prop2(value_p, repos->fs,
                                      rev, propname, TRUE, pool, pool));
    }
  else /* wholly readable revision */
    {
      SVN_ERR(svn_fs_revision_prop2(value_p, repos->fs, rev, propname, TRUE,
                                    pool, pool));
    }

  return SVN_NO_ERROR;
}