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
typedef  int /*<<< orphan*/  svn_auth_ssl_server_cert_info_t ;
typedef  int /*<<< orphan*/  svn_auth_cred_ssl_server_trust_t ;
struct TYPE_2__ {int /*<<< orphan*/  prompt_baton; int /*<<< orphan*/  (* prompt_func ) (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ ssl_server_trust_prompt_provider_baton_t ;
typedef  int apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_AUTH_PARAM_NO_AUTH_CACHE ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_SSL_SERVER_CERT_INFO ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_SSL_SERVER_FAILURES ; 
 int SVN_AUTH_SSL_OTHER ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 void* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
ssl_server_trust_prompt_first_cred(void **credentials_p,
                                   void **iter_baton,
                                   void *provider_baton,
                                   apr_hash_t *parameters,
                                   const char *realmstring,
                                   apr_pool_t *pool)
{
  ssl_server_trust_prompt_provider_baton_t *pb = provider_baton;
  apr_uint32_t *failures = svn_hash_gets(parameters,
                                         SVN_AUTH_PARAM_SSL_SERVER_FAILURES);
  const char *no_auth_cache = svn_hash_gets(parameters,
                                            SVN_AUTH_PARAM_NO_AUTH_CACHE);
  const svn_auth_ssl_server_cert_info_t *cert_info =
    svn_hash_gets(parameters, SVN_AUTH_PARAM_SSL_SERVER_CERT_INFO);
  svn_boolean_t may_save = (!no_auth_cache
                            && !(*failures & SVN_AUTH_SSL_OTHER));

  SVN_ERR(pb->prompt_func((svn_auth_cred_ssl_server_trust_t **)credentials_p,
                          pb->prompt_baton, realmstring, *failures, cert_info,
                          may_save, pool));

  *iter_baton = NULL;
  return SVN_NO_ERROR;
}