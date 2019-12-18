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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/ ** get_field (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

void *tlcomb_store_field (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  char *id = *(IP ++);
  int num = (long)*(IP ++);
#ifdef VLOG
  fprintf (stderr, "store_field: id = %s, num = %d\n", id, num);
#endif

  zval **v = get_field (*arr, id, num);

#ifdef VLOG
  fprintf (stderr, "store_field: field %p\n", v);
#endif
  if (!v) { return 0; }
  *(++arr) = *v;
  TLUNI_NEXT;
}