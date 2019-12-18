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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_repos__config_pool_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  config_access_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  find_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_config__shallow_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_config_read3 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_quick_wrapf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos__create_config_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__destroy_config_access (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos__get_config (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos__config_pool_get(svn_config_t **cfg,
                           svn_repos__config_pool_t *config_pool,
                           const char *path,
                           svn_boolean_t must_exist,
                           svn_repos_t *preferred_repos,
                           apr_pool_t *pool)
{
  svn_error_t *err = SVN_NO_ERROR;
  apr_pool_t *scratch_pool = svn_pool_create(pool);
  config_access_t *access = svn_repos__create_config_access(preferred_repos,
                                                            scratch_pool);
  svn_stream_t *stream;
  svn_checksum_t *checksum;

  *cfg = NULL;
  err = svn_repos__get_config(&stream, &checksum, access, path, must_exist,
                              scratch_pool);
  if (!err)
    err = svn_error_quick_wrapf(find_config(cfg, config_pool, stream,
                                            checksum, pool, scratch_pool),
                                "Error while parsing config file: '%s':",
                                path);

  /* Let the standard implementation handle all the difficult cases.
   * Note that for in-repo configs, there are no further special cases to
   * check for and deal with. */
  if (!*cfg && !svn_path_is_url(path))
    {
      svn_error_clear(err);
      err = svn_config_read3(cfg, path, must_exist, FALSE, FALSE, pool);
    }

  svn_repos__destroy_config_access(access);
  svn_pool_destroy(scratch_pool);

  /* we need to duplicate the root structure as it contains temp. buffers */
  if (*cfg)
    *cfg = svn_config__shallow_copy(*cfg, pool);

  return svn_error_trace(err);
}