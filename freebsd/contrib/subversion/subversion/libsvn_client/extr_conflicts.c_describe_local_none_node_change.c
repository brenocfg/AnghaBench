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
typedef  int /*<<< orphan*/  svn_wc_operation_t ;
typedef  int svn_wc_conflict_reason_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 int svn_client_conflict_get_local_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_operation (int /*<<< orphan*/ *) ; 
#define  svn_wc_conflict_reason_added 136 
#define  svn_wc_conflict_reason_deleted 135 
#define  svn_wc_conflict_reason_edited 134 
#define  svn_wc_conflict_reason_missing 133 
#define  svn_wc_conflict_reason_moved_away 132 
#define  svn_wc_conflict_reason_moved_here 131 
#define  svn_wc_conflict_reason_obstructed 130 
#define  svn_wc_conflict_reason_replaced 129 
#define  svn_wc_conflict_reason_unversioned 128 
 int /*<<< orphan*/  svn_wc_operation_merge ; 
 int /*<<< orphan*/  svn_wc_operation_switch ; 
 int /*<<< orphan*/  svn_wc_operation_update ; 

__attribute__((used)) static svn_error_t *
describe_local_none_node_change(const char **description,
                                svn_client_conflict_t *conflict,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  svn_wc_conflict_reason_t local_change;
  svn_wc_operation_t operation;

  local_change = svn_client_conflict_get_local_change(conflict);
  operation = svn_client_conflict_get_operation(conflict);

  switch (local_change)
    {
    case svn_wc_conflict_reason_edited:
      *description = _("An item containing uncommitted changes was "
                       "found in the working copy.");
      break;
    case svn_wc_conflict_reason_obstructed:
      *description = _("An item which already occupies this path was found in "
                       "the working copy.");
      break;
    case svn_wc_conflict_reason_deleted:
      *description = _("A deleted item was found in the working copy.");
      break;
    case svn_wc_conflict_reason_missing:
      if (operation == svn_wc_operation_update ||
          operation == svn_wc_operation_switch)
        *description = _("No such file or directory was found in the "
                         "working copy.");
      else if (operation == svn_wc_operation_merge)
        {
          /* ### display deleted revision */
          *description = _("No such file or directory was found in the "
                           "merge target working copy.\nThe item may "
                           "have been deleted or moved away in the "
                           "repository's history.");
        }
      break;
    case svn_wc_conflict_reason_unversioned:
      *description = _("An unversioned item was found in the working "
                       "copy.");
      break;
    case svn_wc_conflict_reason_added:
    case svn_wc_conflict_reason_replaced:
      *description = _("An item scheduled to be added to the repository "
                       "in the next commit was found in the working "
                       "copy.");
      break;
    case svn_wc_conflict_reason_moved_away:
      *description = _("The item in the working copy had been moved "
                       "away at the time this conflict was recorded.");
      break;
    case svn_wc_conflict_reason_moved_here:
      *description = _("An item had been moved here in the working copy "
                       "at the time this conflict was recorded.");
      break;
    }

  return SVN_NO_ERROR;
}