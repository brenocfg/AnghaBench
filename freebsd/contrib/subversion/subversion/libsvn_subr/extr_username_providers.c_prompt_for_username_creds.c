#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  prompt_baton; int /*<<< orphan*/  (* prompt_func ) (TYPE_2__**,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ username_prompt_provider_baton_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  may_save; int /*<<< orphan*/  username; } ;
typedef  TYPE_2__ svn_auth_cred_username_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_AUTH_PARAM_DEFAULT_USERNAME ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
prompt_for_username_creds(svn_auth_cred_username_t **cred_p,
                          username_prompt_provider_baton_t *pb,
                          apr_hash_t *parameters,
                          const char *realmstring,
                          svn_boolean_t first_time,
                          svn_boolean_t may_save,
                          apr_pool_t *pool)
{
  const char *def_username = NULL;

  *cred_p = NULL;

  /* If we're allowed to check for default usernames, do so. */
  if (first_time)
    def_username = svn_hash_gets(parameters, SVN_AUTH_PARAM_DEFAULT_USERNAME);

  /* If we have defaults, just build the cred here and return it.
   *
   * ### I do wonder why this is here instead of in a separate
   * ### 'defaults' provider that would run before the prompt
   * ### provider... Hmmm.
   */
  if (def_username)
    {
      *cred_p = apr_palloc(pool, sizeof(**cred_p));
      (*cred_p)->username = apr_pstrdup(pool, def_username);
      (*cred_p)->may_save = TRUE;
    }
  else
    {
      SVN_ERR(pb->prompt_func(cred_p, pb->prompt_baton, realmstring,
                              may_save, pool));
    }

  return SVN_NO_ERROR;
}