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
struct TYPE_8__ {scalar_t__ word; struct TYPE_8__* right; TYPE_1__* item; struct TYPE_8__* left; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_9__ {scalar_t__ item_id; } ;
typedef  TYPE_3__ item_t ;
typedef  scalar_t__ hash_t ;
struct TYPE_7__ {scalar_t__ item_id; } ;

/* Variables and functions */

__attribute__((used)) static tree_t *tree_lookup (tree_t *T, hash_t word, item_t *item) {
  while (T) {
    if (word < T->word) {
      T = T->left;
    } else if (word > T->word) {
      T = T->right;
    } else if (item->item_id < T->item->item_id) {
      T = T->left;
    } else if (item->item_id > T->item->item_id) {
      T = T->right;
    } else {
      return T;
    }
  }
  return T;
}