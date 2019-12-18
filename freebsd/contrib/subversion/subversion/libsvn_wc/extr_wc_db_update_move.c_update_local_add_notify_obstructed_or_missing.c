#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {TYPE_1__* b; int /*<<< orphan*/  local_relpath; } ;
typedef  TYPE_2__ added_node_baton_t ;
struct TYPE_4__ {int /*<<< orphan*/  db; int /*<<< orphan*/  wcroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_wc_notify_skip ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_state_missing ; 
 int /*<<< orphan*/  svn_wc_notify_state_obstructed ; 
 int /*<<< orphan*/  update_move_list_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
update_local_add_notify_obstructed_or_missing(added_node_baton_t *nb,
                                              svn_node_kind_t working_kind,
                                              svn_node_kind_t kind_on_disk,
                                              apr_pool_t *scratch_pool)
{
  svn_wc_notify_state_t content_state;

  if (kind_on_disk == svn_node_none)
      content_state = svn_wc_notify_state_missing;
  else
      content_state = svn_wc_notify_state_obstructed;

  SVN_ERR(update_move_list_add(nb->b->wcroot, nb->local_relpath, nb->b->db,
                               svn_wc_notify_skip, working_kind,
                               content_state, svn_wc_notify_state_inapplicable,
                               NULL, NULL, scratch_pool));
  return SVN_NO_ERROR;
}