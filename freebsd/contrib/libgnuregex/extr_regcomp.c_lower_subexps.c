#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  reg_errcode_t ;
struct TYPE_6__ {TYPE_4__* right; TYPE_4__* left; } ;
typedef  TYPE_2__ bin_tree_t ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_7__ {TYPE_2__* parent; TYPE_1__ token; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_NOERROR ; 
 scalar_t__ SUBEXP ; 
 void* lower_subexp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static reg_errcode_t
lower_subexps (void *extra, bin_tree_t *node)
{
  regex_t *preg = (regex_t *) extra;
  reg_errcode_t err = REG_NOERROR;

  if (node->left && node->left->token.type == SUBEXP)
    {
      node->left = lower_subexp (&err, preg, node->left);
      if (node->left)
	node->left->parent = node;
    }
  if (node->right && node->right->token.type == SUBEXP)
    {
      node->right = lower_subexp (&err, preg, node->right);
      if (node->right)
	node->right->parent = node;
    }

  return err;
}