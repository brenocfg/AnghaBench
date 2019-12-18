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
typedef  int /*<<< orphan*/  range_index_t ;
struct TYPE_4__ {struct TYPE_4__* right; struct TYPE_4__* left; } ;
typedef  TYPE_1__ range_index_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_range_index_node (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
delete_subtree(range_index_t *ndx, range_index_node_t *node)
{
  if (node != NULL)
    {
      delete_subtree(ndx, node->left);
      delete_subtree(ndx, node->right);
      free_range_index_node(ndx, node);
    }
}