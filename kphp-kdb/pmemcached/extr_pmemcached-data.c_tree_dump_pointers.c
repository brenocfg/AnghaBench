#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* right; int /*<<< orphan*/ * x; struct TYPE_3__* left; } ;
typedef  TYPE_1__ tree_t ;
typedef  int /*<<< orphan*/  hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int tree_dump_pointers (tree_t *T, hash_entry_t **x, int p, int maxp) {
  if (!T) {
    return p;
  }
  p = tree_dump_pointers (T->left, x, p, maxp);
  assert (p < maxp);
  x[p ++] = T->x;
  return tree_dump_pointers (T->right, x, p, maxp);
}