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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CONFIG_AUTHN_PASSWORD_KEY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_string_create (char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_auth__simple_password_set(svn_boolean_t *done,
                              apr_hash_t *creds,
                              const char *realmstring,
                              const char *username,
                              const char *password,
                              apr_hash_t *parameters,
                              svn_boolean_t non_interactive,
                              apr_pool_t *pool)
{
  svn_hash_sets(creds, SVN_CONFIG_AUTHN_PASSWORD_KEY,
                svn_string_create(password, pool));
  *done = TRUE;

  return SVN_NO_ERROR;
}