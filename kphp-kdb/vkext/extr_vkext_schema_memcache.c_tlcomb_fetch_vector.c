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
 int /*<<< orphan*/  ALLOC_INIT_ZVAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLUNI_NEXT ; 
 scalar_t__ TLUNI_OK ; 
 scalar_t__ TLUNI_START (void**,void**,int /*<<< orphan*/ **,struct tl_tree**) ; 
 int /*<<< orphan*/  add_index_zval (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ tl_parse_error () ; 
 int tl_parse_int () ; 

void *tlcomb_fetch_vector (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  int n = tl_parse_int ();
  if (tl_parse_error ()) { return 0; }
  ALLOC_INIT_ZVAL (*arr);
  array_init (*arr);
  void **newIP = *(IP ++);

#ifdef VLOG
  fprintf (stderr, "multiplicity %d\n", n);
#endif
  int i;
  for (i = 0; i < n; i++) {
    *(++arr) = 0;
    if (TLUNI_START (newIP, Data, arr, vars) != TLUNI_OK) {
      -- arr;
      return 0;
    }
    add_index_zval (*(arr - 1), i, *arr);
    -- arr;
  }
  TLUNI_NEXT;
}