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
typedef  int /*<<< orphan*/  svn_cmdline_prompt_baton2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  prompt (char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cmdline__auth_gnome_keyring_unlock_prompt(char **keyring_password,
                                              const char *keyring_name,
                                              void *baton,
                                              apr_pool_t *pool)
{
  const char *password;
  const char *pass_prompt;
  svn_cmdline_prompt_baton2_t *pb = baton;

  pass_prompt = apr_psprintf(pool, _("Password for '%s' GNOME keyring: "),
                             keyring_name);
  SVN_ERR(prompt(&password, pass_prompt, TRUE, pb, pool));
  *keyring_password = apr_pstrdup(pool, password);
  return SVN_NO_ERROR;
}