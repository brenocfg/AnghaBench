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
struct TYPE_3__ {int /*<<< orphan*/  conflicted; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  scalar_t__ svn_client_conflict_option_id_t ;
typedef  scalar_t__ svn_boolean_t ;
struct conflict_status_walker_baton {int /*<<< orphan*/  resolved_a_tree_conflict; int /*<<< orphan*/  unresolved_tree_conflicts; int /*<<< orphan*/  conflict_walk_func_baton; int /*<<< orphan*/ * (* conflict_walk_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  handle_tree_conflict_resolution_failure (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_conflicted (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_option_postpone ; 
 scalar_t__ svn_client_conflict_option_unspecified ; 
 scalar_t__ svn_client_conflict_tree_get_resolution (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
conflict_status_walker(void *baton,
                       const char *local_abspath,
                       const svn_wc_status3_t *status,
                       apr_pool_t *scratch_pool)
{
  struct conflict_status_walker_baton *cswb = baton;
  svn_client_conflict_t *conflict;
  svn_error_t *err;
  svn_boolean_t tree_conflicted;

  if (!status->conflicted)
    return SVN_NO_ERROR;

  SVN_ERR(svn_client_conflict_get(&conflict, local_abspath, cswb->ctx,
                                  scratch_pool, scratch_pool));
  SVN_ERR(svn_client_conflict_get_conflicted(NULL, NULL, &tree_conflicted,
                                             conflict, scratch_pool,
                                             scratch_pool));
  err = cswb->conflict_walk_func(cswb->conflict_walk_func_baton,
                                 conflict, scratch_pool);
  if (err)
    {
      if (tree_conflicted)
        SVN_ERR(handle_tree_conflict_resolution_failure(
                  local_abspath, err, cswb->unresolved_tree_conflicts));

      else
        return svn_error_trace(err);
    }

  if (tree_conflicted)
    {
      svn_client_conflict_option_id_t resolution;

      resolution = svn_client_conflict_tree_get_resolution(conflict);
      if (resolution != svn_client_conflict_option_unspecified &&
          resolution != svn_client_conflict_option_postpone)
        cswb->resolved_a_tree_conflict = TRUE;
    }

  return SVN_NO_ERROR;
}