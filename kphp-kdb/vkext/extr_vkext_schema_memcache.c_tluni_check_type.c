#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct tl_tree_type {int children_num; int /*<<< orphan*/ * children; int /*<<< orphan*/  type; } ;
struct tl_tree {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* type ) (void*) ;} ;

/* Variables and functions */
 scalar_t__ NODE_TYPE_TYPE ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 TYPE_1__* TL_TREE_METHODS (struct tl_tree_type*) ; 
 scalar_t__ stub1 (void*) ; 

void *tluni_check_type (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  struct tl_tree_type *res = *(--Data);
//  fprintf (stderr, "res = %p, res->type = %p, *IP = %p, *IP->id = %s\n", res, res->type, *IP, ((struct tl_type *)*IP)->id);

  if (TL_TREE_METHODS (res)->type ((void *)res) != NODE_TYPE_TYPE) {  return 0; }
  if (res->type != *(IP ++)) {  return 0; }
//  if ((res->self.flags & FLAGS_MASK) != (long)*(IP ++)) { return 0; }

  int i;
  for (i = res->children_num - 1; i >= 0; i--) {
    *(Data ++ ) = res->children[i];
  }
  TLUNI_NEXT;
}