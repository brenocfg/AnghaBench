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
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_ra_get_repos_root2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_session_url (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__ensure_ra_session_url(const char **old_session_url,
                                  svn_ra_session_t *ra_session,
                                  const char *session_url,
                                  apr_pool_t *pool)
{
  SVN_ERR(svn_ra_get_session_url(ra_session, old_session_url, pool));
  if (! session_url)
    SVN_ERR(svn_ra_get_repos_root2(ra_session, &session_url, pool));
  if (strcmp(*old_session_url, session_url) != 0)
    SVN_ERR(svn_ra_reparent(ra_session, session_url, pool));
  return SVN_NO_ERROR;
}