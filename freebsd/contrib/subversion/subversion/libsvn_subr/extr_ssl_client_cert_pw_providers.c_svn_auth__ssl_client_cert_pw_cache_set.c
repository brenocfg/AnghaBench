#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  char svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  password; int /*<<< orphan*/  may_save; } ;
typedef  TYPE_1__ svn_auth_cred_ssl_client_cert_pw_t ;
typedef  int /*<<< orphan*/  (* svn_auth__password_set_t ) (char*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char,int /*<<< orphan*/ *) ;
struct TYPE_4__ {int /*<<< orphan*/ * plaintext_answers; int /*<<< orphan*/  prompt_baton; int /*<<< orphan*/  (* plaintext_passphrase_prompt_func ) (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ ssl_client_cert_pw_file_provider_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 char FALSE ; 
 int /*<<< orphan*/  SVN_AUTH_CRED_SSL_CLIENT_CERT_PW ; 
 char const* SVN_AUTH_PARAM_CONFIG_DIR ; 
 char const* SVN_AUTH_PARAM_DONT_STORE_SSL_CLIENT_CERT_PP ; 
 char const* SVN_AUTH_PARAM_NON_INTERACTIVE ; 
 char const* SVN_AUTH_PARAM_NO_AUTH_CACHE ; 
 char const* SVN_AUTH_PARAM_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT ; 
 int /*<<< orphan*/  SVN_AUTH__GNOME_KEYRING_PASSWORD_TYPE ; 
 int /*<<< orphan*/  SVN_AUTH__KEYCHAIN_PASSWORD_TYPE ; 
 int /*<<< orphan*/  SVN_AUTH__KWALLET_PASSWORD_TYPE ; 
 int /*<<< orphan*/  SVN_AUTH__WINCRYPT_PASSWORD_TYPE ; 
 int /*<<< orphan*/  SVN_CONFIG_ASK ; 
 char const* SVN_CONFIG_AUTHN_PASSTYPE_KEY ; 
 int /*<<< orphan*/  SVN_CONFIG_FALSE ; 
 int /*<<< orphan*/  SVN_CONFIG_TRUE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_INVALID_CONFIG_VALUE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 char* apr_palloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_config_write_auth_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_cstring_casecmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,char*) ; 
 char* svn_string_create (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_auth__ssl_client_cert_pw_cache_set(svn_boolean_t *saved,
                                       void *credentials,
                                       void *provider_baton,
                                       apr_hash_t *parameters,
                                       const char *realmstring,
                                       svn_auth__password_set_t passphrase_set,
                                       const char *passtype,
                                       apr_pool_t *pool)
{
  svn_auth_cred_ssl_client_cert_pw_t *creds = credentials;
  apr_hash_t *creds_hash = NULL;
  const char *config_dir;
  svn_error_t *err;
  svn_boolean_t dont_store_passphrase =
    svn_hash_gets(parameters, SVN_AUTH_PARAM_DONT_STORE_SSL_CLIENT_CERT_PP)
    != NULL;
  svn_boolean_t non_interactive =
      svn_hash_gets(parameters, SVN_AUTH_PARAM_NON_INTERACTIVE) != NULL;
  svn_boolean_t no_auth_cache =
    (! creds->may_save)
    || (svn_hash_gets(parameters, SVN_AUTH_PARAM_NO_AUTH_CACHE) != NULL);

  *saved = FALSE;

  if (no_auth_cache)
    return SVN_NO_ERROR;

  config_dir = svn_hash_gets(parameters, SVN_AUTH_PARAM_CONFIG_DIR);
  creds_hash = apr_hash_make(pool);

  /* Don't store passphrase in any form if the user has told
     us not to do so. */
  if (! dont_store_passphrase)
    {
      svn_boolean_t may_save_passphrase = FALSE;

      /* If the passphrase is going to be stored encrypted, go right
         ahead and store it to disk. Else determine whether saving
         in plaintext is OK. */
      if (strcmp(passtype, SVN_AUTH__WINCRYPT_PASSWORD_TYPE) == 0
          || strcmp(passtype, SVN_AUTH__KWALLET_PASSWORD_TYPE) == 0
          || strcmp(passtype, SVN_AUTH__GNOME_KEYRING_PASSWORD_TYPE) == 0
          || strcmp(passtype, SVN_AUTH__KEYCHAIN_PASSWORD_TYPE) == 0)
        {
          may_save_passphrase = TRUE;
        }
      else
        {
#ifdef SVN_DISABLE_PLAINTEXT_PASSWORD_STORAGE
          may_save_passphrase = FALSE;
#else
          const char *store_ssl_client_cert_pp_plaintext =
            svn_hash_gets(parameters,
                          SVN_AUTH_PARAM_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT);
          ssl_client_cert_pw_file_provider_baton_t *b =
            (ssl_client_cert_pw_file_provider_baton_t *)provider_baton;

          if (svn_cstring_casecmp(store_ssl_client_cert_pp_plaintext,
                                  SVN_CONFIG_ASK) == 0)
            {
              if (non_interactive)
                {
                  /* In non-interactive mode, the default behaviour is
                     to not store the passphrase */
                  may_save_passphrase = FALSE;
                }
              else if (b->plaintext_passphrase_prompt_func)
                {
                  /* We're interactive, and the client provided a
                     prompt callback.  So we can ask the user.
                     Check for a cached answer before prompting.

                     This is a pointer-to-boolean, rather than just a
                     boolean, because we must distinguish between
                     "cached answer is no" and "no answer has been
                     cached yet". */
                  svn_boolean_t *cached_answer =
                    svn_hash_gets(b->plaintext_answers, realmstring);

                  if (cached_answer != NULL)
                    {
                      may_save_passphrase = *cached_answer;
                    }
                  else
                    {
                      apr_pool_t *cached_answer_pool;

                      /* Nothing cached for this realm, prompt the user. */
                      SVN_ERR((*b->plaintext_passphrase_prompt_func)(
                                &may_save_passphrase,
                                realmstring,
                                b->prompt_baton,
                                pool));

                      /* Cache the user's answer in case we're called again
                       * for the same realm.
                       *
                       * We allocate the answer cache in the hash table's pool
                       * to make sure that is has the same life time as the
                       * hash table itself. This means that the answer will
                       * survive across RA sessions -- which is important,
                       * because otherwise we'd prompt users once per RA session.
                       */
                      cached_answer_pool = apr_hash_pool_get(b->plaintext_answers);
                      cached_answer = apr_palloc(cached_answer_pool,
                                                 sizeof(*cached_answer));
                      *cached_answer = may_save_passphrase;
                      svn_hash_sets(b->plaintext_answers, realmstring,
                                    cached_answer);
                    }
                }
              else
                {
                  may_save_passphrase = FALSE;
                }
            }
          else if (svn_cstring_casecmp(store_ssl_client_cert_pp_plaintext,
                                       SVN_CONFIG_FALSE) == 0)
            {
              may_save_passphrase = FALSE;
            }
          else if (svn_cstring_casecmp(store_ssl_client_cert_pp_plaintext,
                                       SVN_CONFIG_TRUE) == 0)
            {
              may_save_passphrase = TRUE;
            }
          else
            {
              return svn_error_createf
                (SVN_ERR_RA_DAV_INVALID_CONFIG_VALUE, NULL,
                 _("Config error: invalid value '%s' for option '%s'"),
                store_ssl_client_cert_pp_plaintext,
                SVN_AUTH_PARAM_STORE_SSL_CLIENT_CERT_PP_PLAINTEXT);
            }
#endif
        }

      if (may_save_passphrase)
        {
          SVN_ERR(passphrase_set(saved, creds_hash, realmstring,
                                 NULL, creds->password, parameters,
                                 non_interactive, pool));

          if (*saved && passtype)
            {
              svn_hash_sets(creds_hash, SVN_CONFIG_AUTHN_PASSTYPE_KEY,
                            svn_string_create(passtype, pool));
            }

          /* Save credentials to disk. */
          err = svn_config_write_auth_data(creds_hash,
                                           SVN_AUTH_CRED_SSL_CLIENT_CERT_PW,
                                           realmstring, config_dir, pool);
          svn_error_clear(err);
          *saved = ! err;
        }
    }

  return SVN_NO_ERROR;
}