#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* tree; } ;
typedef  TYPE_1__ range_index_t ;
struct TYPE_5__ {scalar_t__ offset; int /*<<< orphan*/ * prev; struct TYPE_5__* left; struct TYPE_5__* right; } ;
typedef  TYPE_2__ range_index_node_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
splay_range_index(apr_size_t offset, range_index_t *ndx)
{
  range_index_node_t *tree = ndx->tree;
  range_index_node_t scratch_node;
  range_index_node_t *left, *right;

  if (tree == NULL)
    return;

  scratch_node.left = scratch_node.right = NULL;
  left = right = &scratch_node;

  for (;;)
    {
      if (offset < tree->offset)
        {
          if (tree->left != NULL
              && offset < tree->left->offset)
            {
              /* Right rotation */
              range_index_node_t *const node = tree->left;
              tree->left = node->right;
              node->right = tree;
              tree = node;
            }
          if (tree->left == NULL)
            break;

          /* Remember the right subtree */
          right->left = tree;
          right = tree;
          tree = tree->left;
        }
      else if (offset > tree->offset)
        {
          if (tree->right != NULL
              && offset > tree->right->offset)
            {
              /* Left rotation */
              range_index_node_t *const node = tree->right;
              tree->right = node->left;
              node->left = tree;
              tree = node;
            }
          if (tree->right == NULL)
            break;

          /* Remember the left subtree */
          left->right = tree;
          left = tree;
          tree = tree->right;
        }
      else
        break;
    }

  /* Link in the left and right subtrees */
  left->right = tree->left;
  right->left = tree->right;
  tree->left  = scratch_node.right;
  tree->right = scratch_node.left;

  /* The basic top-down splay is finished, but we may still need to
     turn the tree around. What we want is to put the node with the
     largest offset where node->offset <= offset at the top of the
     tree, so that we can insert the new data (or search for existing
     ranges) to the right of the root. This makes cleaning up the
     tree after an insert much simpler, and -- incidentally -- makes
     the whole range index magic work. */
  if (offset < tree->offset && tree->left != NULL)
    {
      if (tree->left->right == NULL)
        {
          /* A single right rotation is enough. */
          range_index_node_t *const node = tree->left;
          tree->left = node->right; /* Which is always NULL. */
          node->right = tree;
          tree = node;
        }
      else
        {
          /* Slide down to the rightmost node in the left subtree. */
          range_index_node_t **nodep = &tree->left;
          while ((*nodep)->right != NULL)
            nodep = &(*nodep)->right;

          /* Now move this node to root in one giant promotion. */
          right = tree;
          left = tree->left;
          tree = *nodep;
          *nodep = tree->left;
          right->left = tree->right; /* Which is always NULL, too. */
          tree->left = left;
          tree->right = right;
        }
    }

  /* Sanity check ... */
  assert((offset >= tree->offset)
         || ((tree->left == NULL)
             && (tree->prev == NULL)));
  ndx->tree = tree;
}