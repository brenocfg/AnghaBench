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
struct tl_tree {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eq ) (struct tl_tree*,struct tl_tree*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TLUNI_NEXT ; 
 TYPE_1__* TL_TREE_METHODS (struct tl_tree*) ; 
 int /*<<< orphan*/  stub1 (struct tl_tree*,struct tl_tree*) ; 

void *tluni_check_type_var (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  struct tl_tree *x = *(--Data);
  struct tl_tree *y = vars[(long)*(IP ++)];
  if (!TL_TREE_METHODS (y)->eq (y, x)) {
    return 0;
  }
  TLUNI_NEXT;
}