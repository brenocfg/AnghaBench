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
typedef  int /*<<< orphan*/  svn_wc_conflict_action_t ;
typedef  int svn_node_kind_t ;

/* Variables and functions */
 char const* _ (char*) ; 
#define  svn_node_dir 136 
#define  svn_node_file 135 
#define  svn_node_none 134 
#define  svn_node_symlink 133 
#define  svn_node_unknown 132 
#define  svn_wc_conflict_action_add 131 
#define  svn_wc_conflict_action_delete 130 
#define  svn_wc_conflict_action_edit 129 
#define  svn_wc_conflict_action_replace 128 
 int /*<<< orphan*/  svn_wc_operation_merge ; 
 int /*<<< orphan*/  svn_wc_operation_switch ; 
 int /*<<< orphan*/  svn_wc_operation_update ; 

__attribute__((used)) static const char *
describe_incoming_change(svn_node_kind_t kind, svn_wc_conflict_action_t action,
                         svn_wc_operation_t operation)
{
  switch (kind)
    {
      case svn_node_file:
      case svn_node_symlink:
        if (operation == svn_wc_operation_update)
          {
            switch (action)
              {
                case svn_wc_conflict_action_edit:
                  return _("An update operation tried to edit a file.");
                case svn_wc_conflict_action_add:
                  return _("An update operation tried to add a file.");
                case svn_wc_conflict_action_delete:
                  return _("An update operation tried to delete or move "
                           "a file.");
                case svn_wc_conflict_action_replace:
                  return _("An update operation tried to replace a file.");
              }
          }
        else if (operation == svn_wc_operation_switch)
          {
            switch (action)
              {
                case svn_wc_conflict_action_edit:
                  return _("A switch operation tried to edit a file.");
                case svn_wc_conflict_action_add:
                  return _("A switch operation tried to add a file.");
                case svn_wc_conflict_action_delete:
                  return _("A switch operation tried to delete or move "
                           "a file.");
                case svn_wc_conflict_action_replace:
                  return _("A switch operation tried to replace a file.");
              }
          }
        else if (operation == svn_wc_operation_merge)
          {
            switch (action)
              {
                case svn_wc_conflict_action_edit:
                  return _("A merge operation tried to edit a file.");
                case svn_wc_conflict_action_add:
                  return _("A merge operation tried to add a file.");
                case svn_wc_conflict_action_delete:
                  return _("A merge operation tried to delete or move "
                           "a file.");
                case svn_wc_conflict_action_replace:
                  return _("A merge operation tried to replace a file.");
            }
          }
        break;
      case svn_node_dir:
        if (operation == svn_wc_operation_update)
          {
            switch (action)
              {
                case svn_wc_conflict_action_edit:
                  return _("An update operation tried to change a directory.");
                case svn_wc_conflict_action_add:
                  return _("An update operation tried to add a directory.");
                case svn_wc_conflict_action_delete:
                  return _("An update operation tried to delete or move "
                           "a directory.");
                case svn_wc_conflict_action_replace:
                  return _("An update operation tried to replace a directory.");
              }
          }
        else if (operation == svn_wc_operation_switch)
          {
            switch (action)
              {
                case svn_wc_conflict_action_edit:
                  return _("A switch operation tried to edit a directory.");
                case svn_wc_conflict_action_add:
                  return _("A switch operation tried to add a directory.");
                case svn_wc_conflict_action_delete:
                  return _("A switch operation tried to delete or move "
                           "a directory.");
                case svn_wc_conflict_action_replace:
                  return _("A switch operation tried to replace a directory.");
              }
          }
        else if (operation == svn_wc_operation_merge)
          {
            switch (action)
              {
                case svn_wc_conflict_action_edit:
                  return _("A merge operation tried to edit a directory.");
                case svn_wc_conflict_action_add:
                  return _("A merge operation tried to add a directory.");
                case svn_wc_conflict_action_delete:
                  return _("A merge operation tried to delete or move "
                           "a directory.");
                case svn_wc_conflict_action_replace:
                  return _("A merge operation tried to replace a directory.");
            }
          }
        break;
      case svn_node_none:
      case svn_node_unknown:
        if (operation == svn_wc_operation_update)
          {
            switch (action)
              {
                case svn_wc_conflict_action_edit:
                  return _("An update operation tried to edit an item.");
                case svn_wc_conflict_action_add:
                  return _("An update operation tried to add an item.");
                case svn_wc_conflict_action_delete:
                  return _("An update operation tried to delete or move "
                           "an item.");
                case svn_wc_conflict_action_replace:
                  return _("An update operation tried to replace an item.");
              }
          }
        else if (operation == svn_wc_operation_switch)
          {
            switch (action)
              {
                case svn_wc_conflict_action_edit:
                  return _("A switch operation tried to edit an item.");
                case svn_wc_conflict_action_add:
                  return _("A switch operation tried to add an item.");
                case svn_wc_conflict_action_delete:
                  return _("A switch operation tried to delete or move "
                           "an item.");
                case svn_wc_conflict_action_replace:
                  return _("A switch operation tried to replace an item.");
              }
          }
        else if (operation == svn_wc_operation_merge)
          {
            switch (action)
              {
                case svn_wc_conflict_action_edit:
                  return _("A merge operation tried to edit an item.");
                case svn_wc_conflict_action_add:
                  return _("A merge operation tried to add an item.");
                case svn_wc_conflict_action_delete:
                  return _("A merge operation tried to delete or move "
                           "an item.");
                case svn_wc_conflict_action_replace:
                  return _("A merge operation tried to replace an item.");
              }
          }
        break;
    }

  return NULL;
}