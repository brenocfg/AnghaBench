#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_boolean_t ;
struct TYPE_6__ {int sequence_number; } ;
struct TYPE_9__ {TYPE_1__ access; } ;
struct TYPE_8__ {TYPE_2__* pattern_sub_nodes; int /*<<< orphan*/  sub_nodes; TYPE_5__ rights; } ;
typedef  TYPE_3__ node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  complex; int /*<<< orphan*/  suffixes; int /*<<< orphan*/  prefixes; TYPE_3__* any_var; TYPE_3__* any; } ;

/* Variables and functions */
 int FALSE ; 
 int NO_SEQUENCE_NUMBER ; 
 int TRUE ; 
 scalar_t__ has_local_rule (TYPE_5__*) ; 
 int trim_subnode_array (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int trim_subnode_hash (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
trim_tree(node_t *node,
          int latest_any_var,
          apr_pool_t *scratch_pool)
{
  svn_boolean_t removed_all = TRUE;

  /* For convenience, we allow NODE to be NULL: */
  if (!node)
    return TRUE;

  /* Do we have a later "any_var" rule at this node. */
  if (   node->pattern_sub_nodes
      && node->pattern_sub_nodes->any_var
      &&   node->pattern_sub_nodes->any_var->rights.access.sequence_number
         > latest_any_var)
    {
      latest_any_var
        = node->pattern_sub_nodes->any_var->rights.access.sequence_number;
    }

  /* Is there a local rule at this node that is not eclipsed by any_var? */
  if (has_local_rule(&node->rights))
    {
      /* Remove the local rule, if it got eclipsed.
       * Note that for the latest any_var node, the sequence number is equal. */
      if (node->rights.access.sequence_number >= latest_any_var)
        removed_all = FALSE;
      else
         node->rights.access.sequence_number = NO_SEQUENCE_NUMBER;
    }

  /* Process all sub-nodes. */
  removed_all &= trim_subnode_hash(&node->sub_nodes, latest_any_var,
                                   scratch_pool);

  if (node->pattern_sub_nodes)
    {
      if (trim_tree(node->pattern_sub_nodes->any, latest_any_var,
                    scratch_pool))
        node->pattern_sub_nodes->any = NULL;
      else
        removed_all = FALSE;

      if (trim_tree(node->pattern_sub_nodes->any_var, latest_any_var,
                    scratch_pool))
        node->pattern_sub_nodes->any_var = NULL;
      else
        removed_all = FALSE;

      removed_all &= trim_subnode_array(&node->pattern_sub_nodes->prefixes,
                                        latest_any_var, scratch_pool);
      removed_all &= trim_subnode_array(&node->pattern_sub_nodes->suffixes,
                                        latest_any_var, scratch_pool);
      removed_all &= trim_subnode_array(&node->pattern_sub_nodes->complex,
                                        latest_any_var, scratch_pool);

      /* Trim the tree as much as possible to speed up lookup(). */
      if (removed_all)
        node->pattern_sub_nodes = NULL;
    }

  return removed_all;
}