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
 int /*<<< orphan*/  TLUNI_NEXT ; 
 int /*<<< orphan*/  do_rpc_store_int (int) ; 
 struct tl_tree* int_to_var_nat_const (int) ; 
 int parse_zend_long (int /*<<< orphan*/ **) ; 

void *tlcomb_store_var_num (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  int var_num = (long)*(IP ++);
  int a = parse_zend_long (arr);
  if (vars[var_num]) {
    DEC_REF (vars[var_num]);
  }
  vars[var_num] = int_to_var_nat_const (a);
  do_rpc_store_int (a);
  TLUNI_NEXT;
}