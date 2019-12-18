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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_REPOS__DB_DIR ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_delete_fs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_delete(const char *path,
                 apr_pool_t *pool)
{
  const char *db_path = svn_dirent_join(path, SVN_REPOS__DB_DIR, pool);

  /* Delete the filesystem environment... */
  SVN_ERR(svn_fs_delete_fs(db_path, pool));

  /* ...then blow away everything else.  */
  return svn_error_trace(svn_io_remove_dir2(path, FALSE, NULL, NULL, pool));
}