#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  conf_path; int /*<<< orphan*/  db_path; int /*<<< orphan*/  fs; int /*<<< orphan*/  fs_type; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION_NO_RETURN () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  check_repos_format (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* create_svn_repos_t (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_repos (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_open2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_type (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_check_path (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

__attribute__((used)) static svn_error_t *
get_repos(svn_repos_t **repos_p,
          const char *path,
          svn_boolean_t exclusive,
          svn_boolean_t nonblocking,
          svn_boolean_t open_fs,
          apr_hash_t *fs_config,
          apr_pool_t *result_pool,
          apr_pool_t *scratch_pool)
{
  svn_repos_t *repos;
  const char *fs_type;

  /* Allocate a repository object. */
  repos = create_svn_repos_t(path, result_pool);

  /* Verify the validity of our repository format. */
  SVN_ERR(check_repos_format(repos, scratch_pool));

  /* Discover the FS type. */
  SVN_ERR(svn_fs_type(&fs_type, repos->db_path, scratch_pool));
  repos->fs_type = apr_pstrdup(result_pool, fs_type);

  /* Lock if needed. */
  SVN_ERR(lock_repos(repos, exclusive, nonblocking, result_pool));

  /* Open up the filesystem only after obtaining the lock. */
  if (open_fs)
    SVN_ERR(svn_fs_open2(&repos->fs, repos->db_path, fs_config,
                         result_pool, scratch_pool));

#ifdef SVN_DEBUG_CRASH_AT_REPOS_OPEN
  /* If $PATH/config/debug-abort exists, crash the server here.
     This debugging feature can be used to test client recovery
     when the server crashes.

     See: Issue #4274 */
  {
    svn_node_kind_t kind;
    svn_error_t *err = svn_io_check_path(
        svn_dirent_join(repos->conf_path, "debug-abort", scratch_pool),
        &kind, scratch_pool);
    svn_error_clear(err);
    if (!err && kind == svn_node_file)
      SVN_ERR_MALFUNCTION_NO_RETURN();
  }
#endif /* SVN_DEBUG_CRASH_AT_REPOS_OPEN */

  *repos_p = repos;
  return SVN_NO_ERROR;
}