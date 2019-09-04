#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  val; struct TYPE_5__* next; } ;
typedef  TYPE_1__ restore_list ;
typedef  int /*<<< orphan*/  map_int_vptr ;

/* Variables and functions */
 int /*<<< orphan*/  CONV_ID (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** map_int_vptr_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * map_int_vptr_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* restore_list_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_list_push_back (TYPE_1__*,int) ; 

int read_restore (int *v, int n, map_int_vptr *h) {
  int i;
  restore_list *cur = NULL;
  for (i = 0; i < n; i++) {
    int x = v[i];
    if (x < 0) {
      cur = restore_list_alloc (CONV_ID (x));
    } else {
      restore_list_push_back (cur, x);
    }
    if (i + 1 == n || v[i + 1] < 0) {
      assert (cur != NULL);
      assert (cur->next != cur);
      assert (map_int_vptr_get (h, cur->val) == NULL);
      *map_int_vptr_add (h, cur->val) = cur;
    }
  }
  return sizeof (int) * n;
}