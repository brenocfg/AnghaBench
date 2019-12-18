#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  username; int /*<<< orphan*/  may_save; } ;
typedef  TYPE_1__ svn_auth_cred_simple_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_AUTH_CRED_USERNAME ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_CONFIG_DIR ; 
 int /*<<< orphan*/  SVN_CONFIG_AUTHN_USERNAME_KEY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_config_write_auth_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_string_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
username_save_creds(svn_boolean_t *saved,
                    void *credentials,
                    void *provider_baton,
                    apr_hash_t *parameters,
                    const char *realmstring,
                    apr_pool_t *pool)
{
  svn_auth_cred_simple_t *creds = credentials;
  apr_hash_t *creds_hash = NULL;
  const char *config_dir;
  svn_error_t *err;

  *saved = FALSE;

  if (! creds->may_save)
    return SVN_NO_ERROR;

  config_dir = svn_hash_gets(parameters, SVN_AUTH_PARAM_CONFIG_DIR);

  /* Put the credentials in a hash and save it to disk */
  creds_hash = apr_hash_make(pool);
  svn_hash_sets(creds_hash, SVN_CONFIG_AUTHN_USERNAME_KEY,
                svn_string_create(creds->username, pool));
  err = svn_config_write_auth_data(creds_hash, SVN_AUTH_CRED_USERNAME,
                                   realmstring, config_dir, pool);
  svn_error_clear(err);
  *saved = ! err;

  return SVN_NO_ERROR;
}