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
struct TYPE_4__ {int eid; scalar_t__ branch_id; int /*<<< orphan*/  rev; } ;
struct TYPE_5__ {scalar_t__ kind; int /*<<< orphan*/  target; int /*<<< orphan*/  text; scalar_t__ props; TYPE_1__ branch_ref; scalar_t__ is_subbranch_root; } ;
typedef  TYPE_2__ svn_element__payload_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 
 scalar_t__ svn_node_unknown ; 

svn_boolean_t
svn_element__payload_invariants(const svn_element__payload_t *payload)
{
  if (payload->is_subbranch_root)
    return TRUE;

  /* If kind is unknown, it's a reference; otherwise it has content
     specified and may also have a reference. */
  if (payload->kind == svn_node_unknown)
    if (SVN_IS_VALID_REVNUM(payload->branch_ref.rev)
        && payload->branch_ref.branch_id
        && payload->branch_ref.eid != -1)
      return TRUE;
  if ((payload->kind == svn_node_dir
       || payload->kind == svn_node_file
       || payload->kind == svn_node_symlink)
      && (payload->props
          && ((payload->kind == svn_node_file) == !!payload->text)
          && ((payload->kind == svn_node_symlink) == !!payload->target)))
    return TRUE;
  return FALSE;
}