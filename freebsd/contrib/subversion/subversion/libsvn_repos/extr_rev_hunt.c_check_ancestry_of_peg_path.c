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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_history_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_fs_history_location (char const**,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_history_prev2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_history2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
check_ancestry_of_peg_path(svn_boolean_t *is_ancestor,
                           svn_fs_t *fs,
                           const char *fs_path,
                           svn_revnum_t peg_revision,
                           svn_revnum_t future_revision,
                           apr_pool_t *pool)
{
  svn_fs_root_t *root;
  svn_fs_history_t *history;
  const char *path = NULL;
  svn_revnum_t revision;
  apr_pool_t *lastpool, *currpool;

  lastpool = svn_pool_create(pool);
  currpool = svn_pool_create(pool);

  SVN_ERR(svn_fs_revision_root(&root, fs, future_revision, pool));

  SVN_ERR(svn_fs_node_history2(&history, root, fs_path, lastpool, lastpool));

  /* Since paths that are different according to strcmp may still be
     equivalent (due to number of consecutive slashes and the fact that
     "" is the same as "/"), we get the "canonical" path in the first
     iteration below so that the comparison after the loop will work
     correctly. */
  fs_path = NULL;

  while (1)
    {
      apr_pool_t *tmppool;

      SVN_ERR(svn_fs_history_prev2(&history, history, TRUE, currpool,
                                   lastpool));

      if (!history)
        break;

      SVN_ERR(svn_fs_history_location(&path, &revision, history, currpool));

      if (!fs_path)
        fs_path = apr_pstrdup(pool, path);

      if (revision <= peg_revision)
        break;

      /* Clear old pool and flip. */
      svn_pool_clear(lastpool);
      tmppool = lastpool;
      lastpool = currpool;
      currpool = tmppool;
    }

  /* We must have had at least one iteration above where we
     reassigned fs_path. Else, the path wouldn't have existed at
     future_revision and svn_fs_history would have thrown. */
  SVN_ERR_ASSERT(fs_path != NULL);

  *is_ancestor = (history && strcmp(path, fs_path) == 0);

  return SVN_NO_ERROR;
}