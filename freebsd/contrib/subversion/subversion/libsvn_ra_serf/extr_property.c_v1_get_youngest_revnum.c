#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {int /*<<< orphan*/  blncache; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_OPTIONS_REQ_FAILED ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  retrieve_baseline_info (int /*<<< orphan*/ *,char const**,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__blncache_get_baseline_info (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__blncache_set (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__fetch_dav_prop (char const**,TYPE_1__*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_urlpath__canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
v1_get_youngest_revnum(svn_revnum_t *youngest,
                       const char **basecoll_url,
                       svn_ra_serf__session_t *session,
                       const char *vcc_url,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  const char *baseline_url;
  const char *bc_url;

  /* Fetching DAV:checked-in from the VCC (with no Label: to specify a
     revision) will return the latest Baseline resource's URL.  */
  SVN_ERR(svn_ra_serf__fetch_dav_prop(&baseline_url, session, vcc_url,
                                      SVN_INVALID_REVNUM,
                                      "checked-in",
                                      scratch_pool, scratch_pool));
  if (!baseline_url)
    {
      return svn_error_create(SVN_ERR_RA_DAV_OPTIONS_REQ_FAILED, NULL,
                              _("The OPTIONS response did not include "
                                "the requested checked-in value"));
    }
  baseline_url = svn_urlpath__canonicalize(baseline_url, scratch_pool);

  /* From the Baseline resource, we can fetch the DAV:baseline-collection
     and DAV:version-name properties. The latter is the revision number,
     which is formally the name used in Label: headers.  */

  /* First check baseline information cache. */
  SVN_ERR(svn_ra_serf__blncache_get_baseline_info(&bc_url,
                                                  youngest,
                                                  session->blncache,
                                                  baseline_url,
                                                  scratch_pool));
  if (!bc_url)
    {
      SVN_ERR(retrieve_baseline_info(youngest, &bc_url, session,
                                     baseline_url, SVN_INVALID_REVNUM,
                                     scratch_pool, scratch_pool));
      SVN_ERR(svn_ra_serf__blncache_set(session->blncache,
                                        baseline_url, *youngest,
                                        bc_url, scratch_pool));
    }

  if (basecoll_url != NULL)
    *basecoll_url = apr_pstrdup(result_pool, bc_url);

  return SVN_NO_ERROR;
}