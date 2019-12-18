#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reg_errcode_t ;
struct TYPE_12__ {TYPE_2__* nodes; } ;
typedef  TYPE_4__ re_dfa_t ;
struct TYPE_11__ {int /*<<< orphan*/  ctx_type; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_3__ opr; } ;
struct TYPE_13__ {int node_idx; TYPE_7__ token; struct TYPE_13__* first; TYPE_1__* left; } ;
typedef  TYPE_5__ bin_tree_t ;
struct TYPE_10__ {int /*<<< orphan*/  constraint; } ;
struct TYPE_9__ {int node_idx; TYPE_5__* first; } ;

/* Variables and functions */
 scalar_t__ ANCHOR ; 
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ CONCAT ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  REG_NOERROR ; 
 int re_dfa_add_node (TYPE_4__*,TYPE_7__) ; 

__attribute__((used)) static reg_errcode_t
calc_first (void *extra, bin_tree_t *node)
{
  re_dfa_t *dfa = (re_dfa_t *) extra;
  if (node->token.type == CONCAT)
    {
      node->first = node->left->first;
      node->node_idx = node->left->node_idx;
    }
  else
    {
      node->first = node;
      node->node_idx = re_dfa_add_node (dfa, node->token);
      if (BE (node->node_idx == -1, 0))
	return REG_ESPACE;
      if (node->token.type == ANCHOR)
	dfa->nodes[node->node_idx].constraint = node->token.opr.ctx_type;
    }
  return REG_NOERROR;
}