#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client__pathrev_t ;
struct TYPE_6__ {int /*<<< orphan*/  url; } ;
struct TYPE_5__ {char const* abspath; TYPE_4__ loc; } ;
typedef  TYPE_1__ merge_target_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_UNRELATED_RESOURCES ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_same_repos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_target_wc (TYPE_1__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__ra_session_from_path2 (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_open_ra_session2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
open_reintegrate_source_and_target(svn_ra_session_t **source_ra_session_p,
                                   svn_client__pathrev_t **source_loc_p,
                                   svn_ra_session_t **target_ra_session_p,
                                   merge_target_t **target_p,
                                   const char *source_path_or_url,
                                   const svn_opt_revision_t *source_peg_revision,
                                   const char *target_abspath,
                                   svn_client_ctx_t *ctx,
                                   apr_pool_t *result_pool,
                                   apr_pool_t *scratch_pool)
{
  svn_client__pathrev_t *source_loc;
  merge_target_t *target;

  /* Open the target WC.  A reintegrate merge requires the merge target to
   * reflect a subtree of the repository as found at a single revision. */
  SVN_ERR(open_target_wc(&target, target_abspath,
                         FALSE, FALSE, FALSE,
                         ctx, scratch_pool, scratch_pool));
  if (! target->loc.url)
    return svn_error_createf(SVN_ERR_CLIENT_UNRELATED_RESOURCES, NULL,
                             _("Can't reintegrate into '%s' because it is "
                               "locally added and therefore not related to "
                               "the merge source"),
                             svn_dirent_local_style(target->abspath,
                                                    scratch_pool));

  SVN_ERR(svn_client_open_ra_session2(target_ra_session_p,
                                      target->loc.url, target->abspath,
                                      ctx, result_pool, scratch_pool));

  SVN_ERR(svn_client__ra_session_from_path2(
            source_ra_session_p, &source_loc,
            source_path_or_url, NULL, source_peg_revision, source_peg_revision,
            ctx, result_pool));

  /* source_loc and target->loc are required to be in the same repository,
     as mergeinfo doesn't come into play for cross-repository merging. */
  SVN_ERR(check_same_repos(source_loc,
                           svn_dirent_local_style(source_path_or_url,
                                                  scratch_pool),
                           &target->loc,
                           svn_dirent_local_style(target->abspath,
                                                  scratch_pool),
                           TRUE /* strict_urls */, scratch_pool));

  *source_loc_p = source_loc;
  *target_p = target;
  return SVN_NO_ERROR;
}