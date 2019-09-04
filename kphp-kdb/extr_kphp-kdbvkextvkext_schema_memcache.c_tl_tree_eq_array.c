#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ flags; } ;
struct tl_tree_array {int args_num; TYPE_2__** args; TYPE_1__ self; } ;
struct tl_tree {int dummy; } ;
struct TYPE_6__ {scalar_t__ (* type ) (void*) ;int /*<<< orphan*/  (* eq ) (struct tl_tree*,struct tl_tree*) ;} ;
struct TYPE_5__ {struct tl_tree* type; scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ NODE_TYPE_ARRAY ; 
 TYPE_3__* TL_TREE_METHODS (struct tl_tree*) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (struct tl_tree*,struct tl_tree*) ; 

int tl_tree_eq_array (struct tl_tree *_x, struct tl_tree *_y) {
  if (TL_TREE_METHODS (_y)->type ((void *)_y) != NODE_TYPE_ARRAY) { return 0; }
  struct tl_tree_array *x = (void *)_x;
  struct tl_tree_array *y = (void *)_y;
  if (x->self.flags != y->self.flags) { return 0; }
  if (x->args_num != y->args_num) { return 0; }
  int i;
  for (i = 0; i < x->args_num; i++) {
    if (!x->args[i]->id) {
      if (y->args[i]->id) { return 0; }
    } else {
      if (!y->args[i]->id) { return 0; }
      if (strcmp (x->args[i]->id, y->args[i]->id)) { return 0; }
    }
    if (!TL_TREE_METHODS (x->args[i]->type)->eq (x->args[i]->type, y->args[i]->type)) {
      return 0;
    }
  }
  return 1;
}