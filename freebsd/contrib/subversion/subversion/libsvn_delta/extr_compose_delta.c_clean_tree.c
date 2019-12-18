#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* tree; } ;
typedef  TYPE_2__ range_index_t ;
struct TYPE_9__ {scalar_t__ offset; scalar_t__ limit; struct TYPE_9__* left; struct TYPE_9__* right; } ;
typedef  TYPE_3__ range_index_node_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_7__ {TYPE_3__* right; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_subtree (TYPE_2__*,TYPE_3__* const) ; 

__attribute__((used)) static void
clean_tree(range_index_t *ndx, apr_size_t limit)
{
  apr_size_t top_offset = limit + 1;
  range_index_node_t **nodep = &ndx->tree->right;
  while (*nodep != NULL)
    {
      range_index_node_t *const node = *nodep;
      apr_size_t const offset =
        (node->right != NULL && node->right->offset < top_offset
         ? node->right->offset
         : top_offset);

      if (node->limit <= limit
          || (node->offset < limit && offset < limit))
        {
          *nodep = node->right;
          node->right = NULL;
          delete_subtree(ndx, node);
        }
      else
        {
          top_offset = node->offset;
          nodep = &node->left;
        }
    }
}