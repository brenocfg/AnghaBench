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
typedef  int /*<<< orphan*/  svn_location_segment_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
struct gls_receiver_baton_t {int /*<<< orphan*/ * pool; int /*<<< orphan*/ * ctx; int /*<<< orphan*/ * segments; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  compare_segments ; 
 int /*<<< orphan*/  gls_receiver ; 
 int /*<<< orphan*/  svn_client__ensure_ra_session_url (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_ra_get_location_segments (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gls_receiver_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sort__array (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_client__repos_location_segments(apr_array_header_t **segments,
                                    svn_ra_session_t *ra_session,
                                    const char *url,
                                    svn_revnum_t peg_revision,
                                    svn_revnum_t start_revision,
                                    svn_revnum_t end_revision,
                                    svn_client_ctx_t *ctx,
                                    apr_pool_t *pool)
{
  struct gls_receiver_baton_t gls_receiver_baton;
  const char *old_session_url;
  svn_error_t *err;

  *segments = apr_array_make(pool, 8, sizeof(svn_location_segment_t *));
  gls_receiver_baton.segments = *segments;
  gls_receiver_baton.ctx = ctx;
  gls_receiver_baton.pool = pool;
  SVN_ERR(svn_client__ensure_ra_session_url(&old_session_url, ra_session,
                                            url, pool));
  err = svn_ra_get_location_segments(ra_session, "", peg_revision,
                                     start_revision, end_revision,
                                     gls_receiver, &gls_receiver_baton,
                                     pool);
  SVN_ERR(svn_error_compose_create(
            err, svn_ra_reparent(ra_session, old_session_url, pool)));
  svn_sort__array(*segments, compare_segments);
  return SVN_NO_ERROR;
}