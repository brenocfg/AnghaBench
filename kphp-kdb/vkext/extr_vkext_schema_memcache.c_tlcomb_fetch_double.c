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
 int /*<<< orphan*/  MAKE_STD_ZVAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,double) ; 
 double tl_parse_double () ; 
 scalar_t__ tl_parse_error () ; 

void *tlcomb_fetch_double (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  double a = tl_parse_double ();
  if (tl_parse_error ()) { return 0; }
  MAKE_STD_ZVAL (*arr);
  ZVAL_DOUBLE (*arr, a);
  TLUNI_NEXT;
}