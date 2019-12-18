#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_boolean_t ;
struct TYPE_7__ {TYPE_2__* tree; } ;
typedef  TYPE_1__ range_index_t ;
struct TYPE_8__ {scalar_t__ offset; scalar_t__ limit; struct TYPE_8__* prev; struct TYPE_8__* next; struct TYPE_8__* right; struct TYPE_8__* left; scalar_t__ target_offset; } ;
typedef  TYPE_2__ range_index_node_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 TYPE_2__* alloc_range_index_node (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_tree (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
insert_range(apr_size_t offset, apr_size_t limit, apr_size_t target_offset,
             range_index_t *ndx)
{
  range_index_node_t *node = NULL;

  if (ndx->tree == NULL)
    {
      node = alloc_range_index_node(ndx, offset, limit, target_offset);
      ndx->tree = node;
    }
  else
    {
      if (offset == ndx->tree->offset
          && limit > ndx->tree->limit)
        {
          ndx->tree->limit = limit;
          ndx->tree->target_offset = target_offset;
          clean_tree(ndx, limit);
        }
      else if (offset > ndx->tree->offset
               && limit > ndx->tree->limit)
        {
          /* We have to make the same sort of checks as clean_tree()
             does for superseded ranges. Have to merge these someday. */

          const svn_boolean_t insert_range_p =
            (!ndx->tree->next
             || ndx->tree->limit < ndx->tree->next->offset
             || limit > ndx->tree->next->limit);

          if (insert_range_p)
            {
              /* Again, we have to check if the new node and the one
                 to the left of the root override root's range. */
              if (ndx->tree->prev && ndx->tree->prev->limit > offset)
                {
                  /* Replace the data in the splayed node. */
                  ndx->tree->offset = offset;
                  ndx->tree->limit = limit;
                  ndx->tree->target_offset = target_offset;
                }
              else
                {
                  /* Insert the range to the right of the splayed node. */
                  node = alloc_range_index_node(ndx, offset, limit,
                                                target_offset);
                  if ((node->next = ndx->tree->next) != NULL)
                    node->next->prev = node;
                  ndx->tree->next = node;
                  node->prev = ndx->tree;

                  node->right = ndx->tree->right;
                  ndx->tree->right = NULL;
                  node->left = ndx->tree;
                  ndx->tree = node;
                }
              clean_tree(ndx, limit);
            }
          else
            /* Ignore the range */;
        }
      else if (offset < ndx->tree->offset)
        {
          assert(ndx->tree->left == NULL);

          /* Insert the range left of the splayed node */
          node = alloc_range_index_node(ndx, offset, limit, target_offset);
          node->left = node->prev = NULL;
          node->right = node->next = ndx->tree;
          ndx->tree = node->next->prev = node;
          clean_tree(ndx, limit);
        }
      else
        /* Ignore the range */;
    }
}