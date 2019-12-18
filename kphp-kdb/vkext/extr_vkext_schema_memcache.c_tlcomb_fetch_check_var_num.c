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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ tl_parse_error () ; 
 int tl_parse_int () ; 
 int var_nat_const_to_int (struct tl_tree*) ; 

void *tlcomb_fetch_check_var_num (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  int x = tl_parse_int ();
#ifdef VLOG
  fprintf (stderr, "%d\n", x);
#endif
  if (tl_parse_error ()) {
    return 0;
  }
  int var_num = (long)*(IP ++);
  if (x != var_nat_const_to_int (vars[var_num])) {
    return 0;
  }
  TLUNI_NEXT;
}