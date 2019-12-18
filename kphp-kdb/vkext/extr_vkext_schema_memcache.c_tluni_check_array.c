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
struct tl_tree_array {long args_num; int /*<<< orphan*/  multiplicity; int /*<<< orphan*/ * args; } ;
struct tl_tree {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* type ) (void*) ;} ;

/* Variables and functions */
 scalar_t__ NODE_TYPE_ARRAY ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 TYPE_1__* TL_TREE_METHODS (struct tl_tree_array*) ; 
 scalar_t__ stub1 (void*) ; 

void *tluni_check_array (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  struct tl_tree_array *res = *(--Data);
  if (TL_TREE_METHODS (res)->type ((void *)res) != NODE_TYPE_ARRAY) {  return 0; }
  if (res->args_num != (long)*(IP ++)) {  return 0; }
  int i;
  for (i = res->args_num - 1; i >= 0; i--) {
    *(Data ++) = res->args[i];
  }
  *(Data ++) = res->multiplicity;
  TLUNI_NEXT;
}