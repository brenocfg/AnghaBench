#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reg_errcode_t ;
struct TYPE_16__ {int has_plural_match; int* nexts; int /*<<< orphan*/  edests; } ;
typedef  TYPE_7__ re_dfa_t ;
struct TYPE_14__ {int type; } ;
struct TYPE_17__ {int node_idx; TYPE_6__* next; TYPE_5__ token; TYPE_4__* right; TYPE_2__* left; } ;
typedef  TYPE_8__ bin_tree_t ;
struct TYPE_15__ {int node_idx; } ;
struct TYPE_13__ {TYPE_3__* first; } ;
struct TYPE_12__ {int node_idx; } ;
struct TYPE_11__ {TYPE_1__* first; } ;
struct TYPE_10__ {int node_idx; } ;

/* Variables and functions */
#define  ANCHOR 135 
#define  CONCAT 134 
#define  END_OF_RE 133 
 int /*<<< orphan*/  IS_EPSILON_NODE (int const) ; 
#define  OP_ALT 132 
#define  OP_BACK_REF 131 
#define  OP_CLOSE_SUBEXP 130 
#define  OP_DUP_ASTERISK 129 
#define  OP_OPEN_SUBEXP 128 
 int /*<<< orphan*/  REG_NOERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  re_node_set_init_1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  re_node_set_init_2 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static reg_errcode_t
link_nfa_nodes (void *extra, bin_tree_t *node)
{
  re_dfa_t *dfa = (re_dfa_t *) extra;
  int idx = node->node_idx;
  reg_errcode_t err = REG_NOERROR;

  switch (node->token.type)
    {
    case CONCAT:
      break;

    case END_OF_RE:
      assert (node->next == NULL);
      break;

    case OP_DUP_ASTERISK:
    case OP_ALT:
      {
	int left, right;
	dfa->has_plural_match = 1;
	if (node->left != NULL)
	  left = node->left->first->node_idx;
	else
	  left = node->next->node_idx;
	if (node->right != NULL)
	  right = node->right->first->node_idx;
	else
	  right = node->next->node_idx;
	assert (left > -1);
	assert (right > -1);
	err = re_node_set_init_2 (dfa->edests + idx, left, right);
      }
      break;

    case ANCHOR:
    case OP_OPEN_SUBEXP:
    case OP_CLOSE_SUBEXP:
      err = re_node_set_init_1 (dfa->edests + idx, node->next->node_idx);
      break;

    case OP_BACK_REF:
      dfa->nexts[idx] = node->next->node_idx;
      if (node->token.type == OP_BACK_REF)
	err = re_node_set_init_1 (dfa->edests + idx, dfa->nexts[idx]);
      break;

    default:
      assert (!IS_EPSILON_NODE (node->token.type));
      dfa->nexts[idx] = node->next->node_idx;
      break;
    }

  return err;
}