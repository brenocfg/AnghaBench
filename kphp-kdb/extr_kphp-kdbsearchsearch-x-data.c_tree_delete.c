#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ word; scalar_t__ y; struct TYPE_9__* left; struct TYPE_9__* right; TYPE_1__* item; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_10__ {long long item_id; } ;
typedef  TYPE_3__ item_t ;
typedef  scalar_t__ hash_t ;
struct TYPE_8__ {long long const item_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_tree_node (TYPE_2__*) ; 

__attribute__((used)) static tree_t *tree_delete (tree_t *T, hash_t word, item_t *item) {
  tree_t *Root = T, **U = &Root, *L, *R;
  const long long item_id = item->item_id;
  while (word != T->word || item_id != T->item->item_id) {
    U = (word < T->word || (word == T->word && item_id < T->item->item_id)) ? &T->left : &T->right;
    T = *U;
    if (!T) { return Root; }
  }

  L = T->left;
  R = T->right;
  free_tree_node (T);
  while (L && R) {
    if (L->y > R->y) {
      *U = L;
      U = &L->right;
      L = *U;
    } else {
      *U = R;
      U = &R->left;
      R = *U;
    }
  }
  *U = L ? L : R;
  return Root;
}