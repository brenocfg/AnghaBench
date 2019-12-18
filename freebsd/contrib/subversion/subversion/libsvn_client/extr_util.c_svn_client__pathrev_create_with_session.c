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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  url; int /*<<< orphan*/  rev; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; } ;
typedef  TYPE_1__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_ra_get_repos_root2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_uuid2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__pathrev_create_with_session(svn_client__pathrev_t **pathrev_p,
                                        svn_ra_session_t *ra_session,
                                        svn_revnum_t rev,
                                        const char *url,
                                        apr_pool_t *result_pool)
{
  svn_client__pathrev_t *pathrev = apr_palloc(result_pool, sizeof(*pathrev));

  SVN_ERR_ASSERT(svn_path_is_url(url));

  SVN_ERR(svn_ra_get_repos_root2(ra_session, &pathrev->repos_root_url,
                                 result_pool));
  SVN_ERR(svn_ra_get_uuid2(ra_session, &pathrev->repos_uuid, result_pool));
  pathrev->rev = rev;
  pathrev->url = apr_pstrdup(result_pool, url);
  *pathrev_p = pathrev;
  return SVN_NO_ERROR;
}