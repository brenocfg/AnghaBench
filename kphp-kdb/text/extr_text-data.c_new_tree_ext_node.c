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
struct TYPE_5__ {int x; int y; int rpos; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ tree_ext_t ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_1__* zmalloc (int) ; 

__attribute__((used)) static inline tree_ext_t *new_tree_ext_node (int x, int y, int rpos) {
  tree_ext_t *P;
  P = zmalloc (sizeof (tree_ext_t));
  assert (P);
  P->left = P->right = NIL;
  P->x = x;
  P->y = y;
  P->rpos = rpos;
//  P->delta = y_to_delta[y & 3];
  return P;
}