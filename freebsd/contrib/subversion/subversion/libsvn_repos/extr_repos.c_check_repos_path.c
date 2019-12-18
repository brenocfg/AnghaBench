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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_REPOS__DB_DIR ; 
 int /*<<< orphan*/  SVN_REPOS__FORMAT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_check_path (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_check_resolved_path (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 

__attribute__((used)) static svn_boolean_t
check_repos_path(const char *path,
                 apr_pool_t *pool)
{
  svn_node_kind_t kind;
  svn_error_t *err;

  err = svn_io_check_path(svn_dirent_join(path, SVN_REPOS__FORMAT, pool),
                          &kind, pool);
  if (err)
    {
      svn_error_clear(err);
      return TRUE;
    }
  if (kind != svn_node_file)
    return FALSE;

  /* Check the db/ subdir, but allow it to be a symlink (Subversion
     works just fine if it's a symlink). */
  err = svn_io_check_resolved_path
    (svn_dirent_join(path, SVN_REPOS__DB_DIR, pool), &kind, pool);
  if (err)
    {
      svn_error_clear(err);
      return TRUE;
    }
  if (kind != svn_node_dir)
    return FALSE;

  return TRUE;
}