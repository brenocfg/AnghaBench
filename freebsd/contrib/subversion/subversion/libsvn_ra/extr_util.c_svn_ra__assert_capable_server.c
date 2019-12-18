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
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_MERGEINFO ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* get_path (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 char const* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/ * svn_ra__assert_mergeinfo_capable_server (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_has_capability (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra__assert_capable_server(svn_ra_session_t *ra_session,
                              const char *capability,
                              const char *path_or_url,
                              apr_pool_t *pool)
{
  if (!strcmp(capability, SVN_RA_CAPABILITY_MERGEINFO))
    return svn_ra__assert_mergeinfo_capable_server(ra_session, path_or_url,
                                                   pool);

  else
    {
      svn_boolean_t has;
      SVN_ERR(svn_ra_has_capability(ra_session, &has, capability, pool));
      if (! has)
        {
          path_or_url = get_path(path_or_url, ra_session, pool);
          return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                 _("The '%s' feature is not supported by '%s'"),
                                 capability,
                                 svn_path_is_url(path_or_url)
                                    ? path_or_url
                                    : svn_dirent_local_style(path_or_url,
                                                             pool));
        }
    }
  return SVN_NO_ERROR;
}