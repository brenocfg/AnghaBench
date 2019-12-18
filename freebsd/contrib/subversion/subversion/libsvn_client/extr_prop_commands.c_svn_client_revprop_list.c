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
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_client__get_revision_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_open_ra_session2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_rev_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_revprop_list(apr_hash_t **props,
                        const char *URL,
                        const svn_opt_revision_t *revision,
                        svn_revnum_t *set_rev,
                        svn_client_ctx_t *ctx,
                        apr_pool_t *pool)
{
  svn_ra_session_t *ra_session;
  apr_hash_t *proplist;
  apr_pool_t *subpool = svn_pool_create(pool);
  svn_error_t *err;

  /* Open an RA session for the URL. Note that we don't have a local
     directory, nor a place to put temp files. */
  SVN_ERR(svn_client_open_ra_session2(&ra_session, URL, NULL,
                                      ctx, subpool, subpool));

  /* Resolve the revision into something real, and return that to the
     caller as well. */
  SVN_ERR(svn_client__get_revision_number(set_rev, NULL, ctx->wc_ctx, NULL,
                                          ra_session, revision, subpool));

  /* The actual RA call. */
  err = svn_ra_rev_proplist(ra_session, *set_rev, &proplist, pool);

  *props = proplist;
  svn_pool_destroy(subpool); /* Close RA session */
  return svn_error_trace(err);
}