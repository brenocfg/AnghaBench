#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct tl_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_REF (struct tl_tree*) ; 
 int /*<<< orphan*/  INC_REF (struct tl_tree*) ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 scalar_t__ TL_IS_NAT_VAR (struct tl_tree*) ; 

void *tluni_set_type_var (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  long p = (long)*(IP ++);
  if (vars[p]) {
    DEC_REF (vars[p]);
  }
  vars[p] = 0;
//  fprintf (stderr, "p = %ld, var = %p, var->type = %s\n", p, vars[p], ((struct tl_tree_type *)vars[p])->type->id);
  vars[p] = *(--Data);
  if (TL_IS_NAT_VAR (vars[p])) {  return 0; }
  INC_REF (vars[p]);
  TLUNI_NEXT;
}