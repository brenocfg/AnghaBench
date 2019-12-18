#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
struct TYPE_15__ {int operation; int /*<<< orphan*/  local_abspath; int /*<<< orphan*/  src_right_version; int /*<<< orphan*/  src_left_version; int /*<<< orphan*/  action; int /*<<< orphan*/  reason; } ;
typedef  TYPE_2__ svn_wc_conflict_description2_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
struct TYPE_16__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_add_tree_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__conflict_skel_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_switch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_set_op_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__db_op_mark_conflict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc__internal_conflicted_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_moved_away ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_moved_here ; 
#define  svn_wc_operation_merge 130 
#define  svn_wc_operation_switch 129 
#define  svn_wc_operation_update 128 

svn_error_t *
svn_wc__add_tree_conflict(svn_wc_context_t *wc_ctx,
                          const svn_wc_conflict_description2_t *conflict,
                          apr_pool_t *scratch_pool)
{
  svn_boolean_t existing_conflict;
  svn_skel_t *conflict_skel;
  svn_error_t *err;

  SVN_ERR_ASSERT(conflict != NULL);
  SVN_ERR_ASSERT(conflict->operation == svn_wc_operation_merge ||
                 (conflict->reason != svn_wc_conflict_reason_moved_away &&
                  conflict->reason != svn_wc_conflict_reason_moved_here));

  /* Re-adding an existing tree conflict victim is an error. */
  err = svn_wc__internal_conflicted_p(NULL, NULL, &existing_conflict,
                                      wc_ctx->db, conflict->local_abspath,
                                      scratch_pool);
  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
        return svn_error_trace(err);

      svn_error_clear(err);
    }
  else if (existing_conflict)
    return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                             _("Attempt to add tree conflict that already "
                               "exists at '%s'"),
                             svn_dirent_local_style(conflict->local_abspath,
                                                    scratch_pool));
  else if (!conflict)
    return SVN_NO_ERROR;

  conflict_skel = svn_wc__conflict_skel_create(scratch_pool);

  SVN_ERR(svn_wc__conflict_skel_add_tree_conflict(conflict_skel, wc_ctx->db,
                                                  conflict->local_abspath,
                                                  conflict->reason,
                                                  conflict->action,
                                                  NULL,
                                                  scratch_pool, scratch_pool));

  switch (conflict->operation)
    {
      case svn_wc_operation_update:
      default:
        SVN_ERR(svn_wc__conflict_skel_set_op_update(conflict_skel,
                                                    conflict->src_left_version,
                                                    conflict->src_right_version,
                                                    scratch_pool, scratch_pool));
        break;
      case svn_wc_operation_switch:
        SVN_ERR(svn_wc__conflict_skel_set_op_switch(conflict_skel,
                                                    conflict->src_left_version,
                                                    conflict->src_right_version,
                                                    scratch_pool, scratch_pool));
        break;
      case svn_wc_operation_merge:
        SVN_ERR(svn_wc__conflict_skel_set_op_merge(conflict_skel,
                                                   conflict->src_left_version,
                                                   conflict->src_right_version,
                                                   scratch_pool, scratch_pool));
        break;
    }

  return svn_error_trace(
                svn_wc__db_op_mark_conflict(wc_ctx->db, conflict->local_abspath,
                                            conflict_skel, NULL, scratch_pool));
}