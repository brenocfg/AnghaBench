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
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 scalar_t__ TLUNI_OK ; 
 scalar_t__ TLUNI_START (void**,void**,int /*<<< orphan*/ **,struct tl_tree**) ; 
 scalar_t__ Z_TYPE_PP (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  do_rpc_store_int (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int get_array_size (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** get_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

void *tlcomb_store_vector (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  void **newIP = *(IP ++);
  if (Z_TYPE_PP (arr) != IS_ARRAY) {
    return 0;
  }
  
  int multiplicity = get_array_size (arr);
  do_rpc_store_int (multiplicity);

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