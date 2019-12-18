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
 int /*<<< orphan*/  TLUNI_NEXT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long,long,long,...) ; 
 int /*<<< orphan*/  stderr ; 
 long var_nat_const_to_int (struct tl_tree*) ; 

void *tlcomb_check_bit (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  long n = (long)*(IP ++);
  long b = (long)*(IP ++);
  long o = (long)*(IP ++);
#ifdef VLOG  
  fprintf (stderr, "check_bit. var_num = %ld, bit_num = %ld, offset = %ld\n", n, b, o);
#endif
  long x = var_nat_const_to_int (vars[n]);
#ifdef VLOG  
  fprintf (stderr, "check_bit. var_num = %ld, bit_num = %ld, offset = %ld, var_value = %ld\n", n, b, o, x);
#endif
  if (!(x & (1 << b))) {
    IP += o;
  }
  TLUNI_NEXT;
}