#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  change_list ;
struct TYPE_3__ {struct TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* chg_list_free ; 
 int /*<<< orphan*/  chg_list_memory ; 
 scalar_t__ dl_get_memory_used () ; 
 TYPE_1__* dl_malloc (int) ; 

void chg_list_init_mem (int n) {
  assert (chg_list_free == NULL);
  assert (n > 0);

  chg_list_memory -= dl_get_memory_used();
  chg_list_free = dl_malloc (sizeof (change_list) * n);
  assert (chg_list_free != NULL);
  chg_list_memory += dl_get_memory_used();

  int i;
  for (i = 0; i + 1 < n; i++) {
    chg_list_free[i].next = &chg_list_free[i + 1];
  }
  chg_list_free[n - 1].next = NULL;
}