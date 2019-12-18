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
struct TYPE_3__ {char const* username; int /*<<< orphan*/  password; int /*<<< orphan*/  may_save; } ;
typedef  TYPE_1__ svn_auth_cred_simple_t ;
typedef  int /*<<< orphan*/  (* svn_auth__password_set_t ) (char*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char,int /*<<< orphan*/ *) ;
struct TYPE_4__ {int /*<<< orphan*/ * plaintext_answers; int /*<<< orphan*/  prompt_baton; int /*<<< orphan*/  (* plaintext_prompt_func ) (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ simple_provider_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 char FALSE ; 
 int /*<<< orphan*/  SVN_AUTH_CRED_SIMPLE ; 
 char const* SVN_AUTH_PARAM_CONFIG_DIR ; 
 char const* SVN_AUTH_PARAM_DONT_STORE_PASSWORDS ; 
 char const* SVN_AUTH_PARAM_NON_INTERACTIVE ; 
 char const* SVN_AUTH_PARAM_NO_AUTH_CACHE ; 
 char const* SVN_AUTH_PARAM_STORE_PLAINTEXT_PASSWORDS ; 
 int /*<<< orphan*/  SVN_AUTH__GNOME_KEYRING_PASSWORD_TYPE ; 
 int /*<<< orphan*/  SVN_AUTH__GPG_AGENT_PASSWORD_TYPE ; 
 int /*<<< orphan*/  SVN_AUTH__KEYCHAIN_PASSWORD_TYPE ; 
 int /*<<< orphan*/  SVN_AUTH__KWALLET_PASSWORD_TYPE ; 
 int /*<<< orphan*/  SVN_AUTH__WINCRYPT_PASSWORD_TYPE ; 
 int /*<<< orphan*/  SVN_CONFIG_ASK ; 
 char const* SVN_CONFIG_AUTHN_PASSTYPE_KEY ; 
 char const* SVN_CONFIG_AUTHN_USERNAME_KEY ; 
 int /*<<< orphan*/  SVN_CONFIG_FALSE ; 
 int /*<<< orphan*/  SVN_CONFIG_TRUE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CONFIG_VALUE ; 
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
svn_auth__simple_creds_cache_set(svn_boolean_t *saved,
                                 void *credentials,
                                 void *provider_baton,
                                 apr_hash_t *parameters,
                                 const char *realmstring,
                                 svn_auth__password_set_t password_set,
                                 const char *passtype,
                                 apr_pool_t *pool)
{
  svn_auth_cred_simple_t *creds = credentials;
  apr_hash_t *creds_hash = NULL;
  const char *config_dir;
  svn_error_t *err;
  svn_boolean_t dont_store_passwords =
    svn_hash_gets(parameters, SVN_AUTH_PARAM_DONT_STORE_PASSWORDS) != NULL;
  svn_boolean_t non_interactive = svn_hash_gets(parameters,
                                                SVN_AUTH_PARAM_NON_INTERACTIVE)
      != NULL;
  svn_boolean_t no_auth_cache =
    (! creds->may_save) || (svn_hash_gets(parameters,
                                          SVN_AUTH_PARAM_NO_AUTH_CACHE)
                            != NULL);

  /* Make sure we've been passed a passtype. */
  SVN_ERR_ASSERT(passtype != NULL);

  *saved = FALSE;

  if (no_auth_cache)
    return SVN_NO_ERROR;

  config_dir = svn_hash_gets(parameters, SVN_AUTH_PARAM_CONFIG_DIR);

  /* Put the username into the credentials hash. */
  creds_hash = apr_hash_make(pool);
  svn_hash_sets(creds_hash, SVN_CONFIG_AUTHN_USERNAME_KEY,
                svn_string_create(creds->username, pool));

  /* Don't store passwords in any form if the user has told
   * us not to do so. */
  if (! dont_store_passwords)
    {
      svn_boolean_t may_save_password = FALSE;

      /* If the password is going to be stored encrypted, go right
       * ahead and store it to disk. Else determine whether saving
       * in plaintext is OK. */
      if (passtype &&
           (strcmp(passtype, SVN_AUTH__WINCRYPT_PASSWORD_TYPE) == 0
            || strcmp(passtype, SVN_AUTH__KEYCHAIN_PASSWORD_TYPE) == 0
            || strcmp(passtype, SVN_AUTH__KWALLET_PASSWORD_TYPE) == 0
            || strcmp(passtype, SVN_AUTH__GNOME_KEYRING_PASSWORD_TYPE) == 0
            || strcmp(passtype, SVN_AUTH__GPG_AGENT_PASSWORD_TYPE) == 0))
        {
          may_save_password = TRUE;
        }
      else
        {
#ifdef SVN_DISABLE_PLAINTEXT_PASSWORD_STORAGE
          may_save_password = FALSE;
#else
          const char *store_plaintext_passwords =
            svn_hash_gets(parameters, SVN_AUTH_PARAM_STORE_PLAINTEXT_PASSWORDS);
          simple_provider_baton_t *b =
            (simple_provider_baton_t *)provider_baton;

          if (store_plaintext_passwords
              && svn_cstring_casecmp(store_plaintext_passwords,
                                     SVN_CONFIG_ASK) == 0)
            {
              if (non_interactive)
                /* In non-interactive mode, the default behaviour is
                 * to not store the password, because it is usually
                 * passed on the command line. */
                may_save_password = FALSE;
              else if (b->plaintext_prompt_func)
                {
                  /* We're interactive, and the client provided a
                   * prompt callback. So we can ask the user.
                   *
                   * Check for a cached answer before prompting. */
                  svn_boolean_t *cached_answer;
                  cached_answer = svn_hash_gets(b->plaintext_answers,
                                                realmstring);
                  if (cached_answer != NULL)
                    may_save_password = *cached_answer;
                  else
                    {
                      apr_pool_t *cached_answer_pool;

                      /* Nothing cached for this realm, prompt the user. */
                      SVN_ERR((*b->plaintext_prompt_func)(&may_save_password,
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
                                                 sizeof(svn_boolean_t));
                      *cached_answer = may_save_password;
                      svn_hash_sets(b->plaintext_answers, realmstring,
                                    cached_answer);
                    }
                }
              else
                {
                  /* TODO: We might want to default to not storing if the
                   * prompt callback is NULL, i.e. have may_save_password
                   * default to FALSE here, in order to force clients to
                   * implement the callback.
                   *
                   * This would change the semantics of old API though.
                   *
                   * So for now, clients that don't implement the callback
                   * and provide no explicit value for
                   * SVN_AUTH_PARAM_STORE_PLAINTEXT_PASSWORDS
                   * cause unencrypted passwords to be stored by default.
                   * Needless to say, our own client is sane, but who knows
                   * what other clients are doing.
                   */
                  may_save_password = TRUE;
                }
            }
          else if (store_plaintext_passwords
                   && svn_cstring_casecmp(store_plaintext_passwords,
                                          SVN_CONFIG_FALSE) == 0)
            {
              may_save_password = FALSE;
            }
          else if (!store_plaintext_passwords
                   || svn_cstring_casecmp(store_plaintext_passwords,
                                          SVN_CONFIG_TRUE) == 0)
            {
              may_save_password = TRUE;
            }
          else
            {
              return svn_error_createf
                (SVN_ERR_BAD_CONFIG_VALUE, NULL,
                 _("Config error: invalid value '%s' for option '%s'"),
                store_plaintext_passwords,
                SVN_AUTH_PARAM_STORE_PLAINTEXT_PASSWORDS);
            }
#endif
        }

      if (may_save_password)
        {
          SVN_ERR(password_set(saved, creds_hash, realmstring,
                               creds->username, creds->password,
                               parameters, non_interactive, pool));
          if (*saved && passtype)
            /* Store the password type with the auth data, so that we
               know which provider owns the password. */
            svn_hash_sets(creds_hash, SVN_CONFIG_AUTHN_PASSTYPE_KEY,
                          svn_string_create(passtype, pool));
        }
    }

  /* Save credentials to disk. */
  err = svn_config_write_auth_data(creds_hash, SVN_AUTH_CRED_SIMPLE,
                                   realmstring, config_dir, pool);
  if (err)
    *saved = FALSE;

  /* ### return error? */
  svn_error_clear(err);

  return SVN_NO_ERROR;
}