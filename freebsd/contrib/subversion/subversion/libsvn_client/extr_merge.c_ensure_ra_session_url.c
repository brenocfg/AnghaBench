#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 scalar_t__ SVN_ERR_RA_ILLEGAL_URL ; 
 TYPE_1__* SVN_NO_ERROR ; 
 TYPE_1__* svn_client_open_ra_session2 (int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
ensure_ra_session_url(svn_ra_session_t **ra_session,
                      const char *url,
                      const char *wri_abspath,
                      svn_client_ctx_t *ctx,
                      apr_pool_t *pool)
{
  svn_error_t *err = SVN_NO_ERROR;

  if (*ra_session)
    {
      err = svn_ra_reparent(*ra_session, url, pool);
    }

  /* SVN_ERR_RA_ILLEGAL_URL is raised when url doesn't point to the same
     repository as ra_session. */
  if (! *ra_session || (err && err->apr_err == SVN_ERR_RA_ILLEGAL_URL))
    {
      svn_error_clear(err);
      err = svn_client_open_ra_session2(ra_session, url, wri_abspath,
                                        ctx, pool, pool);
    }
  SVN_ERR(err);

  return SVN_NO_ERROR;
}