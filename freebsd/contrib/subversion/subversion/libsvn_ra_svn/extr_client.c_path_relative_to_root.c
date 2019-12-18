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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_ILLEGAL_URL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ra_svn_get_repos_root (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 char* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *path_relative_to_root(svn_ra_session_t *session,
                                          const char **rel_path,
                                          const char *url,
                                          apr_pool_t *pool)
{
  const char *root_url;

  SVN_ERR(ra_svn_get_repos_root(session, &root_url, pool));
  *rel_path = svn_uri_skip_ancestor(root_url, url, pool);
  if (! *rel_path)
    return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                             _("'%s' isn't a child of repository root "
                               "URL '%s'"),
                             url, root_url);
  return SVN_NO_ERROR;
}