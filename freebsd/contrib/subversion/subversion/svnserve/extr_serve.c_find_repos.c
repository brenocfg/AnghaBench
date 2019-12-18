#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_repos__config_pool_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_11__ {char const* realm; void* hooks_env; int /*<<< orphan*/  repos; int /*<<< orphan*/  fs; scalar_t__ use_sasl; int /*<<< orphan*/  max_ssf; int /*<<< orphan*/  min_ssf; int /*<<< orphan*/  repos_root; int /*<<< orphan*/  base; int /*<<< orphan*/ * repos_name; int /*<<< orphan*/ * authz_repos_name; int /*<<< orphan*/  repos_url; TYPE_1__* fs_path; int /*<<< orphan*/  capabilities; } ;
typedef  TYPE_3__ repository_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_HOOKS_ENV ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_MAX_SSF ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_MIN_SSF ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_REALM ; 
 char const* SVN_CONFIG_OPTION_USE_SASL ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_GENERAL ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_SASL ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CONFIG_VALUE ; 
 int /*<<< orphan*/  SVN_ERR_BAD_FILENAME ; 
 int /*<<< orphan*/  SVN_ERR_BAD_URL ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_REPOS_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  load_authz_config (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_pwdb_config (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repos_path_valid (char const*) ; 
 int /*<<< orphan*/  set_access (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 
 char* skip_scheme_part (char const*) ; 
 char* strchr (char const*,char) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_config_get (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_config_get_bool (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_cstring_atoui (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_dirent_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_internal_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_dirent_is_child (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  svn_fs_get_uuid (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_component_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_remove_components (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* svn_path_uri_decode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_path_uri_encode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__config_pool_get (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_conf_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_find_root_path (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos_hooks_setenv (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_open3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_remember_client_capabilities (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos_svnserve_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
find_repos(const char *url,
           const char *root,
           svn_boolean_t vhost,
           svn_boolean_t read_only,
           svn_config_t *cfg,
           repository_t *repository,
           svn_repos__config_pool_t *config_pool,
           apr_hash_t *fs_config,
           apr_pool_t *result_pool,
           apr_pool_t *scratch_pool)
{
  const char *path, *full_path, *fs_path, *hooks_env;
  svn_stringbuf_t *url_buf;
  svn_boolean_t sasl_requested;

  /* Skip past the scheme and authority part. */
  path = skip_scheme_part(url);
  if (path == NULL)
    return svn_error_createf(SVN_ERR_BAD_URL, NULL,
                             "Non-svn URL passed to svn server: '%s'", url);

  if (! vhost)
    {
      path = strchr(path, '/');
      if (path == NULL)
        path = "";
    }
  path = svn_relpath_canonicalize(path, scratch_pool);
  path = svn_path_uri_decode(path, scratch_pool);

  /* Ensure that it isn't possible to escape the root by disallowing
     '..' segments. */
  if (!repos_path_valid(path))
    return svn_error_create(SVN_ERR_BAD_FILENAME, NULL,
                            "Couldn't determine repository path");

  /* Join the server-configured root with the client path. */
  full_path = svn_dirent_join(svn_dirent_canonicalize(root, scratch_pool),
                              path, scratch_pool);

  /* Search for a repository in the full path. */
  repository->repos_root = svn_repos_find_root_path(full_path, result_pool);
  if (!repository->repos_root)
    return svn_error_createf(SVN_ERR_RA_SVN_REPOS_NOT_FOUND, NULL,
                             "No repository found in '%s'", url);

  /* Open the repository and fill in b with the resulting information. */
  SVN_ERR(svn_repos_open3(&repository->repos, repository->repos_root,
                          fs_config, result_pool, scratch_pool));
  SVN_ERR(svn_repos_remember_client_capabilities(repository->repos,
                                                 repository->capabilities));
  repository->fs = svn_repos_fs(repository->repos);
  fs_path = full_path + strlen(repository->repos_root);
  repository->fs_path = svn_stringbuf_create(*fs_path ? fs_path : "/",
                                             result_pool);
  url_buf = svn_stringbuf_create(url, result_pool);
  svn_path_remove_components(url_buf,
                        svn_path_component_count(repository->fs_path->data));
  repository->repos_url = url_buf->data;
  repository->authz_repos_name = svn_dirent_is_child(root,
                                                     repository->repos_root,
                                                     result_pool);
  if (repository->authz_repos_name == NULL)
    repository->repos_name = svn_dirent_basename(repository->repos_root,
                                                 result_pool);
  else
    repository->repos_name = repository->authz_repos_name;
  repository->repos_name = svn_path_uri_encode(repository->repos_name,
                                               result_pool);

  /* If the svnserve configuration has not been loaded then load it from the
   * repository. */
  if (NULL == cfg)
    {
      repository->base = svn_repos_conf_dir(repository->repos, result_pool);

      SVN_ERR(svn_repos__config_pool_get(&cfg, config_pool,
                                         svn_repos_svnserve_conf
                                            (repository->repos, result_pool),
                                         FALSE, repository->repos,
                                         result_pool));
    }

  SVN_ERR(load_pwdb_config(repository, cfg, config_pool, result_pool));
  SVN_ERR(load_authz_config(repository, repository->repos_root, cfg,
                            result_pool));

  /* Should we use Cyrus SASL? */
  SVN_ERR(svn_config_get_bool(cfg, &sasl_requested,
                              SVN_CONFIG_SECTION_SASL,
                              SVN_CONFIG_OPTION_USE_SASL, FALSE));
  if (sasl_requested)
    {
#ifdef SVN_HAVE_SASL
      const char *val;

      repository->use_sasl = sasl_requested;

      svn_config_get(cfg, &val, SVN_CONFIG_SECTION_SASL,
                    SVN_CONFIG_OPTION_MIN_SSF, "0");
      SVN_ERR(svn_cstring_atoui(&repository->min_ssf, val));

      svn_config_get(cfg, &val, SVN_CONFIG_SECTION_SASL,
                    SVN_CONFIG_OPTION_MAX_SSF, "256");
      SVN_ERR(svn_cstring_atoui(&repository->max_ssf, val));
#else /* !SVN_HAVE_SASL */
      return svn_error_createf(SVN_ERR_BAD_CONFIG_VALUE, NULL,
                               _("SASL requested but not compiled in; "
                                 "set '%s' to 'false' or recompile "
                                 "svnserve with SASL support"),
                               SVN_CONFIG_OPTION_USE_SASL);
#endif /* SVN_HAVE_SASL */
    }
  else
    {
      repository->use_sasl = FALSE;
    }

  /* Use the repository UUID as the default realm. */
  SVN_ERR(svn_fs_get_uuid(repository->fs, &repository->realm, scratch_pool));
  svn_config_get(cfg, &repository->realm, SVN_CONFIG_SECTION_GENERAL,
                 SVN_CONFIG_OPTION_REALM, repository->realm);
  repository->realm = apr_pstrdup(result_pool, repository->realm);

  /* Make sure it's possible for the client to authenticate.  Note
     that this doesn't take into account any authz configuration read
     above, because we can't know about access it grants until paths
     are given by the client. */
  set_access(repository, cfg, read_only);

  /* Configure hook script environment variables. */
  svn_config_get(cfg, &hooks_env, SVN_CONFIG_SECTION_GENERAL,
                 SVN_CONFIG_OPTION_HOOKS_ENV, NULL);
  if (hooks_env)
    hooks_env = svn_dirent_internal_style(hooks_env, scratch_pool);

  SVN_ERR(svn_repos_hooks_setenv(repository->repos, hooks_env, scratch_pool));
  repository->hooks_env = apr_pstrdup(result_pool, hooks_env);

  return SVN_NO_ERROR;
}