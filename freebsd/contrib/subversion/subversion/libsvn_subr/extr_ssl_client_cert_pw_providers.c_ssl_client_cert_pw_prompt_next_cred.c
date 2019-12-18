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
typedef  int /*<<< orphan*/  svn_auth_cred_ssl_client_cert_pw_t ;
struct TYPE_4__ {scalar_t__ retries; int /*<<< orphan*/  realmstring; TYPE_1__* pb; } ;
typedef  TYPE_2__ ssl_client_cert_pw_prompt_iter_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_3__ {scalar_t__ retry_limit; int /*<<< orphan*/  prompt_baton; int /*<<< orphan*/ * (* prompt_func ) (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_AUTH_PARAM_NO_AUTH_CACHE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
ssl_client_cert_pw_prompt_next_cred(void **credentials_p,
                                    void *iter_baton,
                                    void *provider_baton,
                                    apr_hash_t *parameters,
                                    const char *realmstring,
                                    apr_pool_t *pool)
{
  ssl_client_cert_pw_prompt_iter_baton_t *ib = iter_baton;
  const char *no_auth_cache = svn_hash_gets(parameters,
                                            SVN_AUTH_PARAM_NO_AUTH_CACHE);

  if ((ib->pb->retry_limit >= 0) && (ib->retries >= ib->pb->retry_limit))
    {
      /* give up, go on to next provider. */
      *credentials_p = NULL;
      return SVN_NO_ERROR;
    }
  ib->retries++;

  return ib->pb->prompt_func((svn_auth_cred_ssl_client_cert_pw_t **)
                             credentials_p, ib->pb->prompt_baton,
                             ib->realmstring, ! no_auth_cache, pool);
}