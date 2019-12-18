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
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct svn_auth_baton_t {int /*<<< orphan*/  pool; int /*<<< orphan*/  slave_parameters; } ;
typedef  struct svn_auth_baton_t svn_auth_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_DONT_STORE_PASSWORDS ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_DONT_STORE_SSL_CLIENT_CERT_PP ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_NO_AUTH_CACHE ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_SERVER_GROUP ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_STORE_PLAINTEXT_PASSWORDS ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_SERVERS ; 
 int /*<<< orphan*/  SVN_CONFIG_DEFAULT_OPTION_STORE_AUTH_CREDS ; 
 int /*<<< orphan*/  SVN_CONFIG_DEFAULT_OPTION_STORE_PASSWORDS ; 
 char const* SVN_CONFIG_DEFAULT_OPTION_STORE_PLAINTEXT_PASSWORDS ; 
 int /*<<< orphan*/  SVN_CONFIG_DEFAULT_OPTION_STORE_SSL_CLIENT_CERT_PP ; 
 char const* SVN_CONFIG_DEFAULT_OPTION_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_STORE_AUTH_CREDS ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_STORE_PASSWORDS ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_STORE_PLAINTEXT_PASSWORDS ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_STORE_SSL_CLIENT_CERT_PP ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT ; 
 char const* SVN_CONFIG_SECTION_GLOBAL ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_GROUPS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 struct svn_auth_baton_t* apr_pmemdup (int /*<<< orphan*/ *,struct svn_auth_baton_t const*,int) ; 
 char* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_auth_get_parameter (struct svn_auth_baton_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_auth_set_parameter (struct svn_auth_baton_t*,int /*<<< orphan*/ ,char const*) ; 
 char* svn_config_find_group (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_config_get_yes_no_ask (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_auth__make_session_auth(svn_auth_baton_t **session_auth_baton,
                            const svn_auth_baton_t *auth_baton,
                            apr_hash_t *config,
                            const char *server_name,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  svn_boolean_t store_passwords = SVN_CONFIG_DEFAULT_OPTION_STORE_PASSWORDS;
  svn_boolean_t store_auth_creds = SVN_CONFIG_DEFAULT_OPTION_STORE_AUTH_CREDS;
  const char *store_plaintext_passwords
    = SVN_CONFIG_DEFAULT_OPTION_STORE_PLAINTEXT_PASSWORDS;
  svn_boolean_t store_pp = SVN_CONFIG_DEFAULT_OPTION_STORE_SSL_CLIENT_CERT_PP;
  const char *store_pp_plaintext
    = SVN_CONFIG_DEFAULT_OPTION_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT;
  svn_config_t *servers = NULL;
  const char *server_group = NULL;

  struct svn_auth_baton_t *ab;

  ab = apr_pmemdup(result_pool, auth_baton, sizeof(*ab));

  ab->slave_parameters = apr_hash_make(result_pool);

  /* The 'store-passwords' and 'store-auth-creds' parameters used to
  * live in SVN_CONFIG_CATEGORY_CONFIG. For backward compatibility,
  * if values for these parameters have already been set by our
  * callers, we use those values as defaults.
  *
  * Note that we can only catch the case where users explicitly set
  * "store-passwords = no" or 'store-auth-creds = no".
  *
  * However, since the default value for both these options is
  * currently (and has always been) "yes", users won't know
  * the difference if they set "store-passwords = yes" or
  * "store-auth-creds = yes" -- they'll get the expected behaviour.
  */

  if (svn_auth_get_parameter(ab, SVN_AUTH_PARAM_DONT_STORE_PASSWORDS) != NULL)
    store_passwords = FALSE;

  if (svn_auth_get_parameter(ab, SVN_AUTH_PARAM_NO_AUTH_CACHE) != NULL)
    store_auth_creds = FALSE;

  /* All the svn_auth_set_parameter() calls below this not only affect the
     to be created ra session, but also all the ra sessions that are already
     use this auth baton!

     Please try to key things based on the realm string instead of this
     construct.
 */

  if (config)
    {
      /* Grab the 'servers' config. */
      servers = svn_hash_gets(config, SVN_CONFIG_CATEGORY_SERVERS);
      if (servers)
        {
          /* First, look in the global section. */

          SVN_ERR(svn_config_get_bool
            (servers, &store_passwords, SVN_CONFIG_SECTION_GLOBAL,
             SVN_CONFIG_OPTION_STORE_PASSWORDS,
             store_passwords));

          SVN_ERR(svn_config_get_yes_no_ask
            (servers, &store_plaintext_passwords, SVN_CONFIG_SECTION_GLOBAL,
             SVN_CONFIG_OPTION_STORE_PLAINTEXT_PASSWORDS,
             SVN_CONFIG_DEFAULT_OPTION_STORE_PLAINTEXT_PASSWORDS));

          SVN_ERR(svn_config_get_bool
            (servers, &store_pp, SVN_CONFIG_SECTION_GLOBAL,
             SVN_CONFIG_OPTION_STORE_SSL_CLIENT_CERT_PP,
             store_pp));

          SVN_ERR(svn_config_get_yes_no_ask
            (servers, &store_pp_plaintext,
             SVN_CONFIG_SECTION_GLOBAL,
             SVN_CONFIG_OPTION_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT,
             SVN_CONFIG_DEFAULT_OPTION_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT));

          SVN_ERR(svn_config_get_bool
            (servers, &store_auth_creds, SVN_CONFIG_SECTION_GLOBAL,
              SVN_CONFIG_OPTION_STORE_AUTH_CREDS,
              store_auth_creds));

          /* Find out where we're about to connect to, and
           * try to pick a server group based on the destination. */
          server_group = svn_config_find_group(servers, server_name,
                                               SVN_CONFIG_SECTION_GROUPS,
                                               scratch_pool);

          if (server_group)
            {
              /* Override global auth caching parameters with the ones
               * for the server group, if any. */
              SVN_ERR(svn_config_get_bool(servers, &store_auth_creds,
                                          server_group,
                                          SVN_CONFIG_OPTION_STORE_AUTH_CREDS,
                                          store_auth_creds));

              SVN_ERR(svn_config_get_bool(servers, &store_passwords,
                                          server_group,
                                          SVN_CONFIG_OPTION_STORE_PASSWORDS,
                                          store_passwords));

              SVN_ERR(svn_config_get_yes_no_ask
                (servers, &store_plaintext_passwords, server_group,
                 SVN_CONFIG_OPTION_STORE_PLAINTEXT_PASSWORDS,
                 store_plaintext_passwords));

              SVN_ERR(svn_config_get_bool
                (servers, &store_pp,
                 server_group, SVN_CONFIG_OPTION_STORE_SSL_CLIENT_CERT_PP,
                 store_pp));

              SVN_ERR(svn_config_get_yes_no_ask
                (servers, &store_pp_plaintext, server_group,
                 SVN_CONFIG_OPTION_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT,
                 store_pp_plaintext));
            }
        }
    }

  /* Save auth caching parameters in the auth parameter hash. */
  if (! store_passwords)
    svn_auth_set_parameter(ab, SVN_AUTH_PARAM_DONT_STORE_PASSWORDS, "");

  svn_auth_set_parameter(ab,
                         SVN_AUTH_PARAM_STORE_PLAINTEXT_PASSWORDS,
                         store_plaintext_passwords);

  if (! store_pp)
    svn_auth_set_parameter(ab,
                           SVN_AUTH_PARAM_DONT_STORE_SSL_CLIENT_CERT_PP,
                           "");

  svn_auth_set_parameter(ab,
                         SVN_AUTH_PARAM_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT,
                         store_pp_plaintext);

  if (! store_auth_creds)
    svn_auth_set_parameter(ab, SVN_AUTH_PARAM_NO_AUTH_CACHE, "");

  if (server_group)
    svn_auth_set_parameter(ab,
                           SVN_AUTH_PARAM_SERVER_GROUP,
                           apr_pstrdup(ab->pool, server_group));

  *session_auth_baton = ab;

  return SVN_NO_ERROR;
}