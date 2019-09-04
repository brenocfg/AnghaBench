#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reg_errcode_t ;
struct TYPE_7__ {int type; } ;
struct TYPE_9__ {struct TYPE_9__* next; TYPE_1__* right; TYPE_3__* left; TYPE_2__ token; } ;
typedef  TYPE_4__ bin_tree_t ;
struct TYPE_8__ {TYPE_4__* next; } ;
struct TYPE_6__ {TYPE_4__* next; TYPE_4__* first; } ;

/* Variables and functions */
#define  CONCAT 129 
#define  OP_DUP_ASTERISK 128 
 int /*<<< orphan*/  REG_NOERROR ; 

__attribute__((used)) static reg_errcode_t
calc_next (void *extra, bin_tree_t *node)
{
  switch (node->token.type)
    {
    case OP_DUP_ASTERISK:
      node->left->next = node;
      break;
    case CONCAT:
      node->left->next = node->right->first;
      node->right->next = node->next;
      break;
    default:
      if (node->left)
	node->left->next = node->next;
      if (node->right)
	node->right->next = node->next;
      break;
    }
  return REG_NOERROR;
}