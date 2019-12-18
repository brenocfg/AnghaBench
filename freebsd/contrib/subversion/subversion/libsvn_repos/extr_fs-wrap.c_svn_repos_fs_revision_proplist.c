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
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_proplist2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_check_revision_access (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_repos_revision_access_none ; 
 scalar_t__ svn_repos_revision_access_partial ; 

svn_error_t *
svn_repos_fs_revision_proplist(apr_hash_t **table_p,
                               svn_repos_t *repos,
                               svn_revnum_t rev,
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
      /* Return an empty hash. */
      *table_p = apr_hash_make(pool);
    }
  else if (readability == svn_repos_revision_access_partial)
    {
      apr_hash_t *tmphash;
      svn_string_t *value;

      /* Produce two property hashtables, both in POOL. */
      SVN_ERR(svn_fs_revision_proplist2(&tmphash, repos->fs, rev, TRUE,
                                        pool, pool));
      *table_p = apr_hash_make(pool);

      /* If they exist, we only copy svn:author and svn:date into the
         'real' hashtable being returned. */
      value = svn_hash_gets(tmphash, SVN_PROP_REVISION_AUTHOR);
      if (value)
        svn_hash_sets(*table_p, SVN_PROP_REVISION_AUTHOR, value);

      value = svn_hash_gets(tmphash, SVN_PROP_REVISION_DATE);
      if (value)
        svn_hash_sets(*table_p, SVN_PROP_REVISION_DATE, value);
    }
  else /* wholly readable revision */
    {
      SVN_ERR(svn_fs_revision_proplist2(table_p, repos->fs, rev, TRUE,
                                        pool, pool));
    }

  return SVN_NO_ERROR;
}