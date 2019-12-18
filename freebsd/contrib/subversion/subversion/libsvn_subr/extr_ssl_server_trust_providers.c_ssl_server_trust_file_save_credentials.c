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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  ascii_cert; } ;
typedef  TYPE_1__ svn_auth_ssl_server_cert_info_t ;
struct TYPE_4__ {scalar_t__ accepted_failures; int /*<<< orphan*/  may_save; } ;
typedef  TYPE_2__ svn_auth_cred_ssl_server_trust_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_AUTH_CRED_SSL_SERVER_TRUST ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_CONFIG_DIR ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_SSL_SERVER_CERT_INFO ; 
 int /*<<< orphan*/  SVN_CONFIG_AUTHN_ASCII_CERT_KEY ; 
 int /*<<< orphan*/  SVN_CONFIG_AUTHN_FAILURES_KEY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_write_auth_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 void* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_string_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_createf (int /*<<< orphan*/ *,char*,unsigned long) ; 

__attribute__((used)) static svn_error_t *
ssl_server_trust_file_save_credentials(svn_boolean_t *saved,
                                       void *credentials,
                                       void *provider_baton,
                                       apr_hash_t *parameters,
                                       const char *realmstring,
                                       apr_pool_t *pool)
{
  svn_auth_cred_ssl_server_trust_t *creds = credentials;
  const svn_auth_ssl_server_cert_info_t *cert_info;
  apr_hash_t *creds_hash = NULL;
  const char *config_dir;

  if (! creds->may_save)
    return SVN_NO_ERROR;

  config_dir = svn_hash_gets(parameters, SVN_AUTH_PARAM_CONFIG_DIR);

  cert_info = svn_hash_gets(parameters, SVN_AUTH_PARAM_SSL_SERVER_CERT_INFO);

  creds_hash = apr_hash_make(pool);
  svn_hash_sets(creds_hash, SVN_CONFIG_AUTHN_ASCII_CERT_KEY,
                svn_string_create(cert_info->ascii_cert, pool));
  svn_hash_sets(creds_hash, SVN_CONFIG_AUTHN_FAILURES_KEY,
                svn_string_createf(pool, "%lu",
                                   (unsigned long)creds->accepted_failures));

  SVN_ERR(svn_config_write_auth_data(creds_hash,
                                     SVN_AUTH_CRED_SSL_SERVER_TRUST,
                                     realmstring,
                                     config_dir,
                                     pool));
  *saved = TRUE;
  return SVN_NO_ERROR;
}