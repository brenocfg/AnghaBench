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
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_CONFIG_AUTHN_PASSWORD_KEY ; 
 int /*<<< orphan*/  SVN_CONFIG_AUTHN_USERNAME_KEY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (char*,char const*) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_auth__simple_password_get(svn_boolean_t *done,
                              const char **password,
                              apr_hash_t *creds,
                              const char *realmstring,
                              const char *username,
                              apr_hash_t *parameters,
                              svn_boolean_t non_interactive,
                              apr_pool_t *pool)
{
  svn_string_t *str;

  *done = FALSE;

  str = svn_hash_gets(creds, SVN_CONFIG_AUTHN_USERNAME_KEY);
  if (str && username && strcmp(str->data, username) == 0)
    {
      str = svn_hash_gets(creds, SVN_CONFIG_AUTHN_PASSWORD_KEY);
      if (str && str->data)
        {
          *password = str->data;
          *done = TRUE;
        }
    }

  return SVN_NO_ERROR;
}