#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_auth_cred_simple_t ;
typedef  int /*<<< orphan*/  simple_prompt_provider_baton_t ;
struct TYPE_3__ {scalar_t__ retries; } ;
typedef  TYPE_1__ simple_prompt_iter_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_AUTH_PARAM_NO_AUTH_CACHE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prompt_for_simple_creds (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
simple_prompt_first_creds(void **credentials_p,
                          void **iter_baton,
                          void *provider_baton,
                          apr_hash_t *parameters,
                          const char *realmstring,
                          apr_pool_t *pool)
{
  simple_prompt_provider_baton_t *pb = provider_baton;
  simple_prompt_iter_baton_t *ibaton = apr_pcalloc(pool, sizeof(*ibaton));
  const char *no_auth_cache = svn_hash_gets(parameters,
                                            SVN_AUTH_PARAM_NO_AUTH_CACHE);

  SVN_ERR(prompt_for_simple_creds((svn_auth_cred_simple_t **) credentials_p,
                                  pb, parameters, realmstring, TRUE,
                                  ! no_auth_cache, pool));

  ibaton->retries = 0;
  *iter_baton = ibaton;

  return SVN_NO_ERROR;
}