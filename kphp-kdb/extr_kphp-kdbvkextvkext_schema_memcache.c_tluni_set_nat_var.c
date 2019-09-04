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
typedef  void tl_tree ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_REF (void*) ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 void* int_to_var_nat_const (scalar_t__) ; 
 scalar_t__ var_nat_const_to_int (void*) ; 

void *tluni_set_nat_var (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  long p = (long)*(IP ++);  
  if (vars[p]) {
    DEC_REF (vars[p]);
  }
  vars[p] = 0;
  void *a = *(--Data);
  void *x = int_to_var_nat_const (var_nat_const_to_int (a) + (long)*(IP ++));
  //DEC_REF (a);
  //void *x = *(--Data) + 2 * (long)*(IP ++);
  //fprintf (stderr, "c = %lld\n", (long long)var_nat_const_to_int (x));
  //if (!TL_IS_NAT_VAR (x)) {  return 0; }
  if (var_nat_const_to_int (x) < 0) {  
    DEC_REF (x);
    return 0; 
  }
  vars[p] = x;
  TLUNI_NEXT;
}