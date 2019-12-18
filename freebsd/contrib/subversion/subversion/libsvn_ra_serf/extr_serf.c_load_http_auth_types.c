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
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int SERF_AUTHN_ALL ; 
 int SERF_AUTHN_BASIC ; 
 int SERF_AUTHN_DIGEST ; 
 int SERF_AUTHN_NEGOTIATE ; 
 int SERF_AUTHN_NONE ; 
 int SERF_AUTHN_NTLM ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_HTTP_AUTH_TYPES ; 
 char const* SVN_CONFIG_SECTION_GLOBAL ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CONFIG_VALUE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_collapse_spaces (char*,char const*) ; 
 char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  svn_config_get (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_cstring_casecmp (char*,char*) ; 
 char* svn_cstring_tokenize (char*,char**) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static svn_error_t *
load_http_auth_types(apr_pool_t *pool, svn_config_t *config,
                     const char *server_group,
                     int *authn_types)
{
  const char *http_auth_types = NULL;
  *authn_types = SERF_AUTHN_NONE;

  svn_config_get(config, &http_auth_types, SVN_CONFIG_SECTION_GLOBAL,
               SVN_CONFIG_OPTION_HTTP_AUTH_TYPES, NULL);

  if (server_group)
    {
      svn_config_get(config, &http_auth_types, server_group,
                     SVN_CONFIG_OPTION_HTTP_AUTH_TYPES, http_auth_types);
    }

  if (http_auth_types)
    {
      char *token;
      char *auth_types_list = apr_palloc(pool, strlen(http_auth_types) + 1);
      apr_collapse_spaces(auth_types_list, http_auth_types);
      while ((token = svn_cstring_tokenize(";", &auth_types_list)) != NULL)
        {
          if (svn_cstring_casecmp("basic", token) == 0)
            *authn_types |= SERF_AUTHN_BASIC;
          else if (svn_cstring_casecmp("digest", token) == 0)
            *authn_types |= SERF_AUTHN_DIGEST;
          else if (svn_cstring_casecmp("ntlm", token) == 0)
            *authn_types |= SERF_AUTHN_NTLM;
          else if (svn_cstring_casecmp("negotiate", token) == 0)
            *authn_types |= SERF_AUTHN_NEGOTIATE;
          else
            return svn_error_createf(SVN_ERR_BAD_CONFIG_VALUE, NULL,
                                     _("Invalid config: unknown %s "
                                       "'%s'"),
                                     SVN_CONFIG_OPTION_HTTP_AUTH_TYPES, token);
      }
    }
  else
    {
      /* Nothing specified by the user, so accept all types. */
      *authn_types = SERF_AUTHN_ALL;
    }

  return SVN_NO_ERROR;
}