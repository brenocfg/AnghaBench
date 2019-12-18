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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * get_inheritable_props (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_session_url (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__get_inheritable_props(apr_hash_t **wcroot_iprops,
                                  const char *local_abspath,
                                  svn_revnum_t revision,
                                  svn_depth_t depth,
                                  svn_ra_session_t *ra_session,
                                  svn_client_ctx_t *ctx,
                                  apr_pool_t *result_pool,
                                  apr_pool_t *scratch_pool)
{
  const char *old_session_url;
  svn_error_t *err;

  *wcroot_iprops = NULL;

  if (!SVN_IS_VALID_REVNUM(revision))
    return SVN_NO_ERROR;

  if (ra_session)
    SVN_ERR(svn_ra_get_session_url(ra_session, &old_session_url, scratch_pool));

  /* We just wrap a simple helper function, as it is to easy to leave the ra
     session rooted at some wrong path without a wrapper like this.

     During development we had problems where some now deleted switched path
     made the update try to update to that url instead of the intended url
   */

  err = get_inheritable_props(wcroot_iprops, local_abspath, revision, depth,
                              ra_session, ctx, result_pool, scratch_pool);

  if (ra_session)
    {
      err = svn_error_compose_create(
                err,
                svn_ra_reparent(ra_session, old_session_url, scratch_pool));
    }
  return svn_error_trace(err);
}