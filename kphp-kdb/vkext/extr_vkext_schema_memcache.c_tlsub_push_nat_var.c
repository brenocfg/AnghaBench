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
 int /*<<< orphan*/  TLUNI_NEXT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  int_to_var_nat_const (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ var_nat_const_to_int (void*) ; 

void *tlsub_push_nat_var (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  int p = (long)*(IP ++);
//  *(Data ++) = ((void *)vars[p]) + 2 * (long) *(IP ++);
//  fprintf (stderr, "vars[p] = %p\n", vars[p]);
  *(Data ++) = int_to_var_nat_const (var_nat_const_to_int (vars[p]) + (long) *(IP ++));
#ifdef VLOG
  fprintf (stderr, "Push nat var. Data = %lld\n", var_nat_const_to_int (*(Data - 1)));
#endif
  TLUNI_NEXT;
}