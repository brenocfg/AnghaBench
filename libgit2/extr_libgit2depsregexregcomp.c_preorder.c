#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ reg_errcode_t ;
struct TYPE_5__ {struct TYPE_5__* right; struct TYPE_5__* parent; struct TYPE_5__* left; } ;
typedef  TYPE_1__ bin_tree_t ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_NOERROR ; 

__attribute__((used)) static reg_errcode_t
preorder (bin_tree_t *root, reg_errcode_t (fn (void *, bin_tree_t *)),
	  void *extra)
{
  bin_tree_t *node;

  for (node = root; ; )
    {
      reg_errcode_t err = fn (extra, node);
      if (BE (err != REG_NOERROR, 0))
	return err;

      /* Go to the left node, or up and to the right.  */
      if (node->left)
	node = node->left;
      else
	{
	  bin_tree_t *prev = NULL;
	  while (node->right == prev || node->right == NULL)
	    {
	      prev = node;
	      node = node->parent;
	      if (!node)
		return REG_NOERROR;
	    }
	  node = node->right;
	}
    }
}