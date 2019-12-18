#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_log_entry_receiver_t ;
struct TYPE_10__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_CEASE_INVOCATION ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* svn_client__mergeinfo_log (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_compose_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_ra_get_session_url (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t*
short_circuit_mergeinfo_log(svn_mergeinfo_catalog_t *target_mergeinfo_cat,
                            svn_boolean_t finding_merged,
                            const char *target_path_or_url,
                            const svn_opt_revision_t *target_peg_revision,
                            const char *source_path_or_url,
                            const svn_opt_revision_t *source_peg_revision,
                            const svn_opt_revision_t *source_start_revision,
                            const svn_opt_revision_t *source_end_revision,
                            svn_log_entry_receiver_t receiver,
                            svn_revnum_t *revision,
                            svn_client_ctx_t *ctx,
                            svn_ra_session_t *ra_session,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  apr_array_header_t *revprops;
  svn_error_t *err;
  const char *session_url;

  SVN_ERR(svn_ra_get_session_url(ra_session, &session_url, scratch_pool));

  revprops = apr_array_make(scratch_pool, 0, sizeof(const char *));
  err = svn_client__mergeinfo_log(finding_merged,
                                  target_path_or_url,
                                  target_peg_revision,
                                  target_mergeinfo_cat,
                                  source_path_or_url,
                                  source_peg_revision,
                                  source_start_revision,
                                  source_end_revision,
                                  receiver, revision,
                                  TRUE, svn_depth_infinity,
                                  revprops, ctx, ra_session,
                                  result_pool, scratch_pool);

  err = svn_error_compose_create(
                  err,
                  svn_ra_reparent(ra_session, session_url, scratch_pool));

  if (err)
    {
      /* We expect RECEIVER to short-circuit the (potentially expensive) log
         by raising an SVN_ERR_CEASE_INVOCATION -- see operative_rev_receiver.
         So we can ignore that error, but only as long as we actually found a
         valid revision. */
      if (SVN_IS_VALID_REVNUM(*revision)
          && err->apr_err == SVN_ERR_CEASE_INVOCATION)
        {
          svn_error_clear(err);
          err = NULL;
        }
      else
        {
          return svn_error_trace(err);
        }
    }
  return SVN_NO_ERROR;
}