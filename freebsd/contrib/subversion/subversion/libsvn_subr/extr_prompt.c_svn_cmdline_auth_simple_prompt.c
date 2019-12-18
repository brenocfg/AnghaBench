#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cmdline_prompt_baton2_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  may_save; int /*<<< orphan*/  password; int /*<<< orphan*/  username; } ;
typedef  TYPE_1__ svn_auth_cred_simple_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char const* _ (char*) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  maybe_print_realm (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prompt (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cmdline_auth_simple_prompt(svn_auth_cred_simple_t **cred_p,
                               void *baton,
                               const char *realm,
                               const char *username,
                               svn_boolean_t may_save,
                               apr_pool_t *pool)
{
  svn_auth_cred_simple_t *ret = apr_pcalloc(pool, sizeof(*ret));
  const char *pass_prompt;
  svn_cmdline_prompt_baton2_t *pb = baton;

  SVN_ERR(maybe_print_realm(realm, pool));

  if (username)
    ret->username = apr_pstrdup(pool, username);
  else
    SVN_ERR(prompt(&(ret->username), _("Username: "), FALSE, pb, pool));

  pass_prompt = apr_psprintf(pool, _("Password for '%s': "), ret->username);
  SVN_ERR(prompt(&(ret->password), pass_prompt, TRUE, pb, pool));
  ret->may_save = may_save;
  *cred_p = ret;
  return SVN_NO_ERROR;
}