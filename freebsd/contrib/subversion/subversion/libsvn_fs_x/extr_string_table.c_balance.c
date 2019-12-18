#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  builder_table_t ;
struct TYPE_4__ {scalar_t__ depth; struct TYPE_4__* right; struct TYPE_4__* left; } ;
typedef  TYPE_1__ builder_string_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
balance(builder_table_t *table,
        builder_string_t **parent,
        builder_string_t *node)
{
  apr_size_t left_height = node->left ? node->left->depth + 1 : 0;
  apr_size_t right_height = node->right ? node->right->depth + 1 : 0;

  if (left_height > right_height + 1)
    {
      builder_string_t *temp = node->left->right;
      node->left->right = node;
      *parent = node->left;
      node->left = temp;

      --left_height;
    }
  else if (left_height + 1 < right_height)
    {
      builder_string_t *temp = node->right->left;
      *parent = node->right;
      node->right->left = node;
      node->right = temp;

      --right_height;
    }

  node->depth = MAX(left_height, right_height);
}