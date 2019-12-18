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
 int /*<<< orphan*/  MAKE_STD_ZVAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 struct tl_tree* int_to_var_nat_const (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ tl_parse_error () ; 
 int tl_parse_int () ; 

void *tlcomb_fetch_var_num (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  int x = tl_parse_int ();
#ifdef VLOG
  fprintf (stderr, "%d\n", x);
#endif
  if (tl_parse_error ()) {
    return 0;
  }
  MAKE_STD_ZVAL (*arr);
  ZVAL_LONG (*arr, x);
  int var_num = (long)*(IP ++);
  if (vars[var_num]) {
    DEC_REF (vars[var_num]);
  }
  vars[var_num] = int_to_var_nat_const (x);
  
  TLUNI_NEXT;
}