#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reg_errcode_t ;
struct TYPE_14__ {int* subexp_map; int used_bkref_map; } ;
typedef  TYPE_6__ re_dfa_t ;
typedef  int bitset_word_t ;
struct TYPE_12__ {int idx; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_4__ opr; } ;
struct TYPE_15__ {TYPE_5__ token; TYPE_3__* left; } ;
typedef  TYPE_7__ bin_tree_t ;
struct TYPE_9__ {int idx; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_1__ opr; } ;
struct TYPE_11__ {TYPE_7__* parent; struct TYPE_11__* left; TYPE_2__ token; } ;

/* Variables and functions */
 int BITSET_WORD_BITS ; 
 scalar_t__ OP_BACK_REF ; 
 int /*<<< orphan*/  REG_NOERROR ; 
 scalar_t__ SUBEXP ; 

__attribute__((used)) static reg_errcode_t
optimize_subexps (void *extra, bin_tree_t *node)
{
  re_dfa_t *dfa = (re_dfa_t *) extra;

  if (node->token.type == OP_BACK_REF && dfa->subexp_map)
    {
      int idx = node->token.opr.idx;
      node->token.opr.idx = dfa->subexp_map[idx];
      dfa->used_bkref_map |= 1 << node->token.opr.idx;
    }

  else if (node->token.type == SUBEXP
	   && node->left && node->left->token.type == SUBEXP)
    {
      int other_idx = node->left->token.opr.idx;

      node->left = node->left->left;
      if (node->left)
	node->left->parent = node;

      dfa->subexp_map[other_idx] = dfa->subexp_map[node->token.opr.idx];
      if (other_idx < BITSET_WORD_BITS)
	  dfa->used_bkref_map &= ~((bitset_word_t) 1 << other_idx);
    }

  return REG_NOERROR;
}