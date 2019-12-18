#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_6__ {char* path; } ;
struct TYPE_7__ {TYPE_1__ session_url; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_baseline_info (char const**,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__get_relative_path (char const**,char const*,TYPE_2__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__get_stable_url(const char **stable_url,
                            svn_revnum_t *latest_revnum,
                            svn_ra_serf__session_t *session,
                            const char *url,
                            svn_revnum_t revision,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  const char *basecoll_url;
  const char *repos_relpath;
  svn_revnum_t revnum_used;

  /* No URL? No sweat. We'll use the session URL.  */
  if (! url)
    url = session->session_url.path;

  SVN_ERR(get_baseline_info(&basecoll_url, &revnum_used,
                            session, revision, scratch_pool, scratch_pool));
  SVN_ERR(svn_ra_serf__get_relative_path(&repos_relpath, url,
                                         session, scratch_pool));

  *stable_url = svn_path_url_add_component2(basecoll_url, repos_relpath,
                                            result_pool);
  if (latest_revnum)
    *latest_revnum = revnum_used;

  return SVN_NO_ERROR;
}