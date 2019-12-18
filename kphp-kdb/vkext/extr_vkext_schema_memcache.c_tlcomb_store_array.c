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
 int /*<<< orphan*/  DEC_REF (void*) ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 scalar_t__ TLUNI_OK ; 
 scalar_t__ TLUNI_START (void**,void**,int /*<<< orphan*/ **,struct tl_tree**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/ ** get_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int var_nat_const_to_int (void*) ; 

void *tlcomb_store_array (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  void **newIP = *(IP ++);
  int multiplicity = var_nat_const_to_int (*(--Data));
#ifdef VLOG  
  fprintf (stderr, "multiplicity %d. *arr = %p\n", multiplicity, *arr);
#endif
  DEC_REF (*Data);
  int i;
  for (i = 0; i < multiplicity; i++) {
    zval **w = get_field (*arr, 0, i);
    #ifdef VLOG  
      fprintf (stderr, "field = %p\n", w ? *w : 0);
    #endif
    if (!w) { return 0; }
    *(++arr) = *w;
    if (TLUNI_START (newIP, Data, arr, vars) != TLUNI_OK) {
      -- arr;
      return 0;
    }
    -- arr;
  }
  TLUNI_NEXT;
}