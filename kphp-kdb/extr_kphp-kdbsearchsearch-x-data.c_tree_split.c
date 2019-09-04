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
struct TYPE_9__ {scalar_t__ word; struct TYPE_9__* right; struct TYPE_9__* left; TYPE_1__* item; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_10__ {scalar_t__ item_id; } ;
typedef  TYPE_3__ item_t ;
typedef  scalar_t__ hash_t ;
struct TYPE_8__ {scalar_t__ item_id; } ;

/* Variables and functions */

__attribute__((used)) static void tree_split (tree_t **L, tree_t **R, tree_t *T, hash_t word, item_t *item) {
  if (!T) { *L = *R = 0; return; }
  if (word < T->word || (word == T->word && item->item_id < T->item->item_id)) {
    *R = T;
    tree_split (L, &T->left, T->left, word, item);
  } else {
    *L = T;
    tree_split (&T->right, R, T->right, word, item);
  }
}