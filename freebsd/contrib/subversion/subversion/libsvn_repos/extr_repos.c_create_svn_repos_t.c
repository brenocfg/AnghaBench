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
struct TYPE_4__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  repository_capabilities; int /*<<< orphan*/ * hooks_env_path; void* lock_path; void* hook_path; void* conf_path; void* db_path; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_REPOS__CONF_DIR ; 
 int /*<<< orphan*/  SVN_REPOS__DB_DIR ; 
 int /*<<< orphan*/  SVN_REPOS__HOOK_DIR ; 
 int /*<<< orphan*/  SVN_REPOS__LOCK_DIR ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 void* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_repos_t *
create_svn_repos_t(const char *path, apr_pool_t *pool)
{
  svn_repos_t *repos = apr_pcalloc(pool, sizeof(*repos));

  repos->path = apr_pstrdup(pool, path);
  repos->db_path = svn_dirent_join(path, SVN_REPOS__DB_DIR, pool);
  repos->conf_path = svn_dirent_join(path, SVN_REPOS__CONF_DIR, pool);
  repos->hook_path = svn_dirent_join(path, SVN_REPOS__HOOK_DIR, pool);
  repos->lock_path = svn_dirent_join(path, SVN_REPOS__LOCK_DIR, pool);
  repos->hooks_env_path = NULL;
  repos->repository_capabilities = apr_hash_make(pool);
  repos->pool = pool;

  return repos;
}