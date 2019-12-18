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
typedef  int /*<<< orphan*/  ltree_x_t ;
struct TYPE_4__ {struct TYPE_4__* left; struct TYPE_4__* right; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ ltree_t ;

/* Variables and functions */
 int ltree_x_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ltree_t *ltree_lookup (ltree_t *T, ltree_x_t x) {
  while (T) {
    int c = ltree_x_compare (x, T->x);
    if (!c) {
      return T;
    }
    T = (c > 0 ? T->right : T->left);
  }
  return T;
}