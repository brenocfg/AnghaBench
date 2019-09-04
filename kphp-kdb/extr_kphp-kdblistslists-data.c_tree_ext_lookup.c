#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* right; struct TYPE_5__* left; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_ext_small_t ;
typedef  int /*<<< orphan*/  object_id_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int object_id_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree_ext_small_t *tree_ext_lookup (tree_ext_small_t *T, object_id_t x) {
  int p = 0;
  while (T != NIL && (p = object_id_compare (x, T->x)) != 0) {
    T = (p < 0) ? T->left : T->right;
  }
  return T;
}