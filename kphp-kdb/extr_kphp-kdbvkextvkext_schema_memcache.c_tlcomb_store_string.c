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
 int /*<<< orphan*/  do_rpc_store_string (char*,int) ; 
 char* parse_zend_string (int /*<<< orphan*/ **,int*) ; 

void *tlcomb_store_string (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  int len;
  char *s = parse_zend_string (arr, &len);
  do_rpc_store_string (s, len);
  TLUNI_NEXT;
}