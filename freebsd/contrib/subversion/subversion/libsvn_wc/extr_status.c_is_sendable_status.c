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
struct TYPE_4__ {scalar_t__ repos_node_status; scalar_t__ node_status; scalar_t__ moved_to_abspath; scalar_t__ changelist; scalar_t__ lock; scalar_t__ versioned; scalar_t__ switched; scalar_t__ conflicted; scalar_t__ repos_lock; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
struct TYPE_5__ {int /*<<< orphan*/  op_root; TYPE_1__ s; } ;
typedef  TYPE_2__ svn_wc__internal_status_t ;
typedef  scalar_t__ svn_boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ svn_wc_status_deleted ; 
 scalar_t__ svn_wc_status_ignored ; 
 scalar_t__ svn_wc_status_none ; 
 scalar_t__ svn_wc_status_normal ; 
 scalar_t__ svn_wc_status_unversioned ; 

__attribute__((used)) static svn_boolean_t
is_sendable_status(const svn_wc__internal_status_t *i_status,
                   svn_boolean_t no_ignore,
                   svn_boolean_t get_all)
{
  const svn_wc_status3_t *status = &i_status->s;
  /* If the repository status was touched at all, it's interesting. */
  if (status->repos_node_status != svn_wc_status_none)
    return TRUE;

  /* If there is a lock in the repository, send it. */
  if (status->repos_lock)
    return TRUE;

  if (status->conflicted)
    return TRUE;

  /* If the item is ignored, and we don't want ignores, skip it. */
  if ((status->node_status == svn_wc_status_ignored) && (! no_ignore))
    return FALSE;

  /* If we want everything, we obviously want this single-item subset
     of everything. */
  if (get_all)
    return TRUE;

  /* If the item is unversioned, display it. */
  if (status->node_status == svn_wc_status_unversioned)
    return TRUE;

  /* If the text, property or tree state is interesting, send it. */
  if ((status->node_status != svn_wc_status_none)
       && (status->node_status != svn_wc_status_normal)
       && !(status->node_status == svn_wc_status_deleted
            && !i_status->op_root))
    return TRUE;

  /* If it's switched, send it. */
  if (status->switched)
    return TRUE;

  /* If there is a lock token, send it. */
  if (status->versioned && status->lock)
    return TRUE;

  /* If the entry is associated with a changelist, send it. */
  if (status->changelist)
    return TRUE;

  if (status->moved_to_abspath)
    return TRUE;

  /* Otherwise, don't send it. */
  return FALSE;
}