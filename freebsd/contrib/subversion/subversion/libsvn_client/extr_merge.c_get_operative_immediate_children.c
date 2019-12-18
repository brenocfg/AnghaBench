#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
struct TYPE_3__ {char const* merge_source_fspath; char const* merge_target_abspath; int /*<<< orphan*/ * result_pool; int /*<<< orphan*/ * wc_ctx; scalar_t__ depth; int /*<<< orphan*/ * operative_children; } ;
typedef  TYPE_1__ log_find_operative_subtree_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_log (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_find_operative_subtree_revs ; 
 scalar_t__ svn_depth_infinity ; 

__attribute__((used)) static svn_error_t *
get_operative_immediate_children(apr_hash_t **operative_children,
                                 const char *merge_source_fspath,
                                 svn_revnum_t oldest_rev,
                                 svn_revnum_t youngest_rev,
                                 const char *merge_target_abspath,
                                 svn_depth_t depth,
                                 svn_wc_context_t *wc_ctx,
                                 svn_ra_session_t *ra_session,
                                 apr_pool_t *result_pool,
                                 apr_pool_t *scratch_pool)
{
  log_find_operative_subtree_baton_t log_baton;

  SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(oldest_rev));
  SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(youngest_rev));
  SVN_ERR_ASSERT(oldest_rev <= youngest_rev);

  *operative_children = apr_hash_make(result_pool);

  if (depth == svn_depth_infinity)
    return SVN_NO_ERROR;

  /* Now remove any paths from *OPERATIVE_CHILDREN that are inoperative when
     merging MERGE_SOURCE_REPOS_PATH -r(OLDEST_REV - 1):YOUNGEST_REV to
     MERGE_TARGET_ABSPATH at --depth infinity. */
  log_baton.operative_children = *operative_children;
  log_baton.merge_source_fspath = merge_source_fspath;
  log_baton.merge_target_abspath = merge_target_abspath;
  log_baton.depth = depth;
  log_baton.wc_ctx = wc_ctx;
  log_baton.result_pool = result_pool;

  SVN_ERR(get_log(ra_session, "", youngest_rev, oldest_rev,
                  TRUE, /* discover_changed_paths */
                  log_find_operative_subtree_revs,
                  &log_baton, scratch_pool));

  return SVN_NO_ERROR;
}