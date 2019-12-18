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
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
struct TYPE_6__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_7__ {scalar_t__ nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_INVALID_OPERATION_DEPTH ; 
 int /*<<< orphan*/  revert (int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  revert_changelist (int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  revert_partial (int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 scalar_t__ svn_depth_infinity ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_from_cstring_keys (int /*<<< orphan*/ **,TYPE_2__ const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_revert5(svn_wc_context_t *wc_ctx,
               const char *local_abspath,
               svn_depth_t depth,
               svn_boolean_t use_commit_times,
               const apr_array_header_t *changelist_filter,
               svn_boolean_t clear_changelists,
               svn_boolean_t metadata_only,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               svn_wc_notify_func2_t notify_func,
               void *notify_baton,
               apr_pool_t *scratch_pool)
{
  if (changelist_filter && changelist_filter->nelts)
    {
      apr_hash_t *changelist_hash;

      SVN_ERR(svn_hash_from_cstring_keys(&changelist_hash, changelist_filter,
                                         scratch_pool));
      return svn_error_trace(revert_changelist(wc_ctx->db, local_abspath,
                                               depth, use_commit_times,
                                               changelist_hash,
                                               clear_changelists,
                                               metadata_only,
                                               cancel_func, cancel_baton,
                                               notify_func, notify_baton,
                                               scratch_pool));
    }

  if (depth == svn_depth_empty || depth == svn_depth_infinity)
    return svn_error_trace(revert(wc_ctx->db, local_abspath,
                                  depth, use_commit_times, clear_changelists,
                                  metadata_only,
                                  cancel_func, cancel_baton,
                                  notify_func, notify_baton,
                                  scratch_pool));

  /* The user may expect svn_depth_files/svn_depth_immediates to work
     on copied dirs with one level of children.  It doesn't, the user
     will get an error and will need to invoke an infinite revert.  If
     we identified those cases where svn_depth_infinity would not
     revert too much we could invoke the recursive call above. */

  if (depth == svn_depth_files || depth == svn_depth_immediates)
    return svn_error_trace(revert_partial(wc_ctx->db, local_abspath,
                                          depth, use_commit_times,
                                          clear_changelists, metadata_only,
                                          cancel_func, cancel_baton,
                                          notify_func, notify_baton,
                                          scratch_pool));

  /* Bogus depth. Tell the caller.  */
  return svn_error_create(SVN_ERR_WC_INVALID_OPERATION_DEPTH, NULL, NULL);
}