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
typedef  int /*<<< orphan*/  svn_wc_conflict_reason_t ;
typedef  int svn_node_kind_t ;

/* Variables and functions */
 char const* _ (char*) ; 
#define  svn_node_dir 141 
#define  svn_node_file 140 
#define  svn_node_none 139 
#define  svn_node_symlink 138 
#define  svn_node_unknown 137 
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

__attribute__((used)) static const char *
local_reason_str(svn_node_kind_t kind, svn_wc_conflict_reason_t reason,
                 svn_wc_operation_t operation)
{
  switch (kind)
    {
      case svn_node_file:
      case svn_node_symlink:
        switch (reason)
          {
          case svn_wc_conflict_reason_edited:
            return _("local file edit");
          case svn_wc_conflict_reason_obstructed:
            return _("local file obstruction");
          case svn_wc_conflict_reason_deleted:
            return _("local file delete");
          case svn_wc_conflict_reason_missing:
            if (operation == svn_wc_operation_merge)
              return _("local file missing or deleted or moved away");
            else
              return _("local file missing");
          case svn_wc_conflict_reason_unversioned:
            return _("local file unversioned");
          case svn_wc_conflict_reason_added:
            return _("local file add");
          case svn_wc_conflict_reason_replaced:
            return _("local file replace");
          case svn_wc_conflict_reason_moved_away:
            return _("local file moved away");
          case svn_wc_conflict_reason_moved_here:
            return _("local file moved here");
          }
        break;
      case svn_node_dir:
        switch (reason)
          {
          case svn_wc_conflict_reason_edited:
            return _("local dir edit");
          case svn_wc_conflict_reason_obstructed:
            return _("local dir obstruction");
          case svn_wc_conflict_reason_deleted:
            return _("local dir delete");
          case svn_wc_conflict_reason_missing:
            if (operation == svn_wc_operation_merge)
              return _("local dir missing or deleted or moved away");
            else
              return _("local dir missing");
          case svn_wc_conflict_reason_unversioned:
            return _("local dir unversioned");
          case svn_wc_conflict_reason_added:
            return _("local dir add");
          case svn_wc_conflict_reason_replaced:
            return _("local dir replace");
          case svn_wc_conflict_reason_moved_away:
            return _("local dir moved away");
          case svn_wc_conflict_reason_moved_here:
            return _("local dir moved here");
          }
        break;
      case svn_node_none:
      case svn_node_unknown:
        switch (reason)
          {
          case svn_wc_conflict_reason_edited:
            return _("local edit");
          case svn_wc_conflict_reason_obstructed:
            return _("local obstruction");
          case svn_wc_conflict_reason_deleted:
            return _("local delete");
          case svn_wc_conflict_reason_missing:
            if (operation == svn_wc_operation_merge)
              return _("local missing or deleted or moved away");
            else
              return _("local missing");
          case svn_wc_conflict_reason_unversioned:
            return _("local unversioned");
          case svn_wc_conflict_reason_added:
            return _("local add");
          case svn_wc_conflict_reason_replaced:
            return _("local replace");
          case svn_wc_conflict_reason_moved_away:
            return _("local moved away");
          case svn_wc_conflict_reason_moved_here:
            return _("local moved here");
          }
        break;
    }
  return NULL;
}