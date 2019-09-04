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
typedef  int /*<<< orphan*/  hash_entry ;
struct TYPE_3__ {struct TYPE_3__* next_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dl_get_memory_used () ; 
 TYPE_1__* dl_malloc (int) ; 
 int htbl_allocated_cnt ; 
 TYPE_1__* htbl_free_entries ; 
 int /*<<< orphan*/  htbl_memory ; 

void htbl_init_mem (int n) {
  assert (htbl_free_entries == NULL);
  assert (n > 0);

  htbl_memory -= dl_get_memory_used();
  htbl_free_entries = dl_malloc (sizeof (hash_entry) * n);
  assert (htbl_free_entries != NULL);
  htbl_memory += dl_get_memory_used();

  htbl_allocated_cnt += n;

  int i;
  for (i = 0; i + 1 < n; i++) {
    htbl_free_entries[i].next_entry = &htbl_free_entries[i + 1];
  }
  htbl_free_entries[n - 1].next_entry = NULL;
}