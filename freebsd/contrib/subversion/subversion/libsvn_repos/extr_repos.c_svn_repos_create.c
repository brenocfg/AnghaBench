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
struct TYPE_6__ {int /*<<< orphan*/  format; int /*<<< orphan*/  db_path; int /*<<< orphan*/  fs; int /*<<< orphan*/  fs_type; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FS_TYPE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_BAD_ARGS ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FS_TYPE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_PRE_1_4_COMPATIBLE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS__FORMAT ; 
 int /*<<< orphan*/  SVN_REPOS__FORMAT_NUMBER ; 
 int /*<<< orphan*/  SVN_REPOS__FORMAT_NUMBER_LEGACY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  create_repos_structure (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* create_svn_repos_t (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_repos (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_create2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_hash__get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash__get_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_write_version_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_repos_find_root_path (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_create(svn_repos_t **repos_p,
                 const char *path,
                 const char *unused_1,
                 const char *unused_2,
                 apr_hash_t *config,
                 apr_hash_t *fs_config,
                 apr_pool_t *result_pool)
{
  svn_repos_t *repos;
  svn_error_t *err;
  apr_pool_t *scratch_pool = svn_pool_create(result_pool);
  const char *root_path;
  const char *local_abspath;

  /* Allocate a repository object, filling in the format we will create. */
  repos = create_svn_repos_t(path, result_pool);
  repos->format = SVN_REPOS__FORMAT_NUMBER;

  /* Discover the type of the filesystem we are about to create. */
  repos->fs_type = svn_hash__get_cstring(fs_config, SVN_FS_CONFIG_FS_TYPE,
                                         DEFAULT_FS_TYPE);
  if (svn_hash__get_bool(fs_config, SVN_FS_CONFIG_PRE_1_4_COMPATIBLE, FALSE))
    repos->format = SVN_REPOS__FORMAT_NUMBER_LEGACY;

  /* Don't create a repository inside another repository. */
  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, scratch_pool));
  root_path = svn_repos_find_root_path(local_abspath, scratch_pool);
  if (root_path != NULL)
    {
      if (strcmp(root_path, local_abspath) == 0)
        return svn_error_createf(SVN_ERR_REPOS_BAD_ARGS, NULL,
                                 _("'%s' is an existing repository"),
                                 svn_dirent_local_style(root_path,
                                                        scratch_pool));
      else
        return svn_error_createf(SVN_ERR_REPOS_BAD_ARGS, NULL,
                                 _("'%s' is a subdirectory of an existing "
                                   "repository " "rooted at '%s'"),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool),
                                 svn_dirent_local_style(root_path,
                                                        scratch_pool));
    }

  /* Create the various files and subdirectories for the repository. */
  SVN_ERR_W(create_repos_structure(repos, path, fs_config, scratch_pool),
            _("Repository creation failed"));

  /* Lock if needed. */
  SVN_ERR(lock_repos(repos, FALSE, FALSE, scratch_pool));

  /* Create an environment for the filesystem. */
  if ((err = svn_fs_create2(&repos->fs, repos->db_path, fs_config,
                            result_pool, scratch_pool)))
    {
      /* If there was an error making the filesytem, e.g. unknown/supported
       * filesystem type.  Clean up after ourselves.  Yes this is safe because
       * create_repos_structure will fail if the path existed before we started
       * so we can't accidentally remove a directory that previously existed.
       */
      svn_pool_destroy(scratch_pool); /* Release lock to allow deleting dir */

      return svn_error_trace(
                   svn_error_compose_create(
                        err,
                        svn_io_remove_dir2(path, FALSE, NULL, NULL,
                                           result_pool)));
    }

  /* This repository is ready.  Stamp it with a format number. */
  SVN_ERR(svn_io_write_version_file
          (svn_dirent_join(path, SVN_REPOS__FORMAT, scratch_pool),
           repos->format, scratch_pool));

  svn_pool_destroy(scratch_pool); /* Release lock */

  *repos_p = repos;
  return SVN_NO_ERROR;
}