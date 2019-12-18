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
 int /*<<< orphan*/  do_rpc_store_int (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int parse_zend_long (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 

void *tlcomb_store_int (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  int a = parse_zend_long (arr);
#ifdef VLOG
  fprintf (stderr, "Got int %d (0x%08x)\n", a, a);
#endif
  do_rpc_store_int (a);
  TLUNI_NEXT;
}