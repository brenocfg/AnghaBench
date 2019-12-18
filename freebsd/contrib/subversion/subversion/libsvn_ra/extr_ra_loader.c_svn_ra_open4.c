#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/ * pool; TYPE_3__ const* vtable; void* cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_27__ {int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  auth_baton; } ;
typedef  TYPE_2__ svn_ra_callbacks2_t ;
struct TYPE_28__ {scalar_t__ (* get_schemes ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_uuid ) (TYPE_1__*,char const**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_svn_ra_open ) (TYPE_1__*,TYPE_5__* (*) (TYPE_1__**,char const**,char const*,char const*,TYPE_2__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ;TYPE_5__* (* open_session ) (TYPE_1__*,char const**,char const*,TYPE_2__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_version ) () ;} ;
typedef  TYPE_3__ svn_ra__vtable_t ;
typedef  int /*<<< orphan*/  (* svn_ra__init_func_t ) (int /*<<< orphan*/ ,TYPE_3__ const**,int /*<<< orphan*/ *) ;
struct TYPE_29__ {scalar_t__ apr_err; } ;
typedef  TYPE_5__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  svn_auth_baton_t ;
struct ra_lib_defn {char const* ra_name; scalar_t__ schemes; int /*<<< orphan*/  (* initfunc ) (int /*<<< orphan*/ ,TYPE_3__ const**,int /*<<< orphan*/ *) ;} ;
struct TYPE_30__ {int /*<<< orphan*/ * hostname; } ;
typedef  TYPE_6__ apr_uri_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 char* DEFAULT_HTTP_LIBRARY ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_SERVERS ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_HTTP_LIBRARY ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_GROUPS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CONFIG_VALUE ; 
 int /*<<< orphan*/  SVN_ERR_RA_CANNOT_CREATE_SESSION ; 
 int /*<<< orphan*/  SVN_ERR_RA_ILLEGAL_URL ; 
 scalar_t__ SVN_ERR_RA_SESSION_URL_MISMATCH ; 
 int /*<<< orphan*/  SVN_ERR_RA_UUID_MISMATCH ; 
 TYPE_5__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ apr_uri_parse (int /*<<< orphan*/ *,char const*,TYPE_6__*) ; 
 int /*<<< orphan*/  check_ra_version (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ dav_schemes ; 
 char* has_scheme_of (scalar_t__,char const*) ; 
 int /*<<< orphan*/  load_ra_module (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,TYPE_3__ const**,int /*<<< orphan*/ *),int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 struct ra_lib_defn* ra_libraries ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *) ; 
 TYPE_5__* stub3 (TYPE_1__*,char const**,char const*,TYPE_2__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,TYPE_5__* (*) (TYPE_1__**,char const**,char const*,char const*,TYPE_2__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_auth__make_session_auth (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_config_find_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_config_get_server_setting (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* svn_error_createf (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char const*,...) ; 
 TYPE_5__* svn_error_trace (TYPE_5__*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_version () ; 

svn_error_t *svn_ra_open4(svn_ra_session_t **session_p,
                          const char **corrected_url_p,
                          const char *repos_URL,
                          const char *uuid,
                          const svn_ra_callbacks2_t *callbacks,
                          void *callback_baton,
                          apr_hash_t *config,
                          apr_pool_t *pool)
{
  apr_pool_t *sesspool = svn_pool_create(pool);
  apr_pool_t *scratch_pool = svn_pool_create(sesspool);
  svn_ra_session_t *session;
  const struct ra_lib_defn *defn;
  const svn_ra__vtable_t *vtable = NULL;
  apr_uri_t repos_URI;
  apr_status_t apr_err;
  svn_error_t *err;
#ifdef CHOOSABLE_DAV_MODULE
  const char *http_library = DEFAULT_HTTP_LIBRARY;
#endif
  svn_auth_baton_t *auth_baton;

  /* Initialize the return variable. */
  *session_p = NULL;

  apr_err = apr_uri_parse(sesspool, repos_URL, &repos_URI);
  /* ### Should apr_uri_parse leave hostname NULL?  It doesn't
   * for "file:///" URLs, only for bogus URLs like "bogus".
   * If this is the right behavior for apr_uri_parse, maybe we
   * should have a svn_uri_parse wrapper. */
  if (apr_err != APR_SUCCESS || repos_URI.hostname == NULL)
    return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                             _("Illegal repository URL '%s'"),
                             repos_URL);

  if (callbacks->auth_baton)
    SVN_ERR(svn_auth__make_session_auth(&auth_baton,
                                        callbacks->auth_baton, config,
                                        repos_URI.hostname,
                                        sesspool, scratch_pool));
  else
    auth_baton = NULL;

#ifdef CHOOSABLE_DAV_MODULE
  if (config)
    {
      svn_config_t *servers = NULL;
      const char *server_group = NULL;

      /* Grab the 'servers' config. */
      servers = svn_hash_gets(config, SVN_CONFIG_CATEGORY_SERVERS);
      if (servers)
        {
          /* First, look in the global section. */

          /* Find out where we're about to connect to, and
           * try to pick a server group based on the destination. */
          server_group = svn_config_find_group(servers, repos_URI.hostname,
                                               SVN_CONFIG_SECTION_GROUPS,
                                               sesspool);

          /* Now, which DAV-based RA method do we want to use today? */
          http_library
            = svn_config_get_server_setting(servers,
                                            server_group, /* NULL is OK */
                                            SVN_CONFIG_OPTION_HTTP_LIBRARY,
                                            DEFAULT_HTTP_LIBRARY);

          if (strcmp(http_library, "serf") != 0)
            return svn_error_createf(SVN_ERR_BAD_CONFIG_VALUE, NULL,
                                     _("Invalid config: unknown HTTP library "
                                       "'%s'"),
                                     http_library);
        }
    }
#endif

  /* Find the library. */
  for (defn = ra_libraries; defn->ra_name != NULL; ++defn)
    {
      const char *scheme;

      if ((scheme = has_scheme_of(defn->schemes, repos_URL)))
        {
          svn_ra__init_func_t initfunc = defn->initfunc;

#ifdef CHOOSABLE_DAV_MODULE
          if (defn->schemes == dav_schemes
              && strcmp(defn->ra_name, http_library) != 0)
            continue;
#endif

          if (! initfunc)
            SVN_ERR(load_ra_module(&initfunc, NULL, defn->ra_name,
                                   scratch_pool));
          if (! initfunc)
            /* Library not found. */
            continue;

          SVN_ERR(initfunc(svn_ra_version(), &vtable, scratch_pool));

          SVN_ERR(check_ra_version(vtable->get_version(), scheme));

          if (! has_scheme_of(vtable->get_schemes(scratch_pool), repos_URL))
            /* Library doesn't support the scheme at runtime. */
            continue;


          break;
        }
    }

  if (vtable == NULL)
    return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                             _("Unrecognized URL scheme for '%s'"),
                             repos_URL);

  /* Create the session object. */
  session = apr_pcalloc(sesspool, sizeof(*session));
  session->cancel_func = callbacks->cancel_func;
  session->cancel_baton = callback_baton;
  session->vtable = vtable;
  session->pool = sesspool;

  /* Ask the library to open the session. */
  err = vtable->open_session(session, corrected_url_p,
                             repos_URL,
                             callbacks, callback_baton, auth_baton,
                             config, sesspool, scratch_pool);

  if (err)
    {
      svn_pool_destroy(sesspool); /* Includes scratch_pool */
      if (err->apr_err == SVN_ERR_RA_SESSION_URL_MISMATCH)
        return svn_error_trace(err);

      return svn_error_createf(
                SVN_ERR_RA_CANNOT_CREATE_SESSION, err,
                _("Unable to connect to a repository at URL '%s'"),
                repos_URL);
    }

  /* If the session open stuff detected a server-provided URL
     correction (a 301 or 302 redirect response during the initial
     OPTIONS request), then kill the session so the caller can decide
     what to do. */
  if (corrected_url_p && *corrected_url_p)
    {
      /* *session_p = NULL; */
      *corrected_url_p = apr_pstrdup(pool, *corrected_url_p);
      svn_pool_destroy(sesspool); /* Includes scratch_pool */
      return SVN_NO_ERROR;
    }

  if (vtable->set_svn_ra_open)
    SVN_ERR(vtable->set_svn_ra_open(session, svn_ra_open4));

  /* Check the UUID. */
  if (uuid)
    {
      const char *repository_uuid;

      SVN_ERR(vtable->get_uuid(session, &repository_uuid, pool));
      if (strcmp(uuid, repository_uuid) != 0)
        {
          /* Duplicate the uuid as it is allocated in sesspool */
          repository_uuid = apr_pstrdup(pool, repository_uuid);
          svn_pool_destroy(sesspool); /* includes scratch_pool */
          return svn_error_createf(SVN_ERR_RA_UUID_MISMATCH, NULL,
                                   _("Repository UUID '%s' doesn't match "
                                     "expected UUID '%s'"),
                                   repository_uuid, uuid);
        }
    }

  svn_pool_destroy(scratch_pool);
  *session_p = session;
  return SVN_NO_ERROR;
}