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
 int /*<<< orphan*/  do_rpc_store_long (long long) ; 
 long long parse_zend_long (int /*<<< orphan*/ **) ; 

void *tlcomb_store_long (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  long long a = parse_zend_long (arr);
  do_rpc_store_long (a);
  TLUNI_NEXT;
}