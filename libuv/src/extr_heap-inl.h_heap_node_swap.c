#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct heap_node {struct heap_node* right; struct heap_node* parent; struct heap_node* left; } ;
struct heap {struct heap_node* min; } ;

/* Variables and functions */

__attribute__((used)) static void heap_node_swap(struct heap* heap,
                           struct heap_node* parent,
                           struct heap_node* child) {
  struct heap_node* sibling;
  struct heap_node t;

  t = *parent;
  *parent = *child;
  *child = t;

  parent->parent = child;
  if (child->left == child) {
    child->left = parent;
    sibling = child->right;
  } else {
    child->right = parent;
    sibling = child->left;
  }
  if (sibling != NULL)
    sibling->parent = child;

  if (parent->left != NULL)
    parent->left->parent = parent;
  if (parent->right != NULL)
    parent->right->parent = parent;

  if (child->parent == NULL)
    heap->min = child;
  else if (child->parent->left == parent)
    child->parent->left = child;
  else
    child->parent->right = child;
}