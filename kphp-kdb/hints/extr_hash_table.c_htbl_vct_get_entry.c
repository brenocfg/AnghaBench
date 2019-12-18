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
typedef  TYPE_1__* hash_entry_vct_ptr ;
struct TYPE_5__ {struct TYPE_5__* next_entry; } ;
typedef  TYPE_1__ hash_entry_vct ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int htbl_vct_allocated_cnt ; 
 TYPE_1__* htbl_vct_free_entries ; 
 int /*<<< orphan*/  htbl_vct_init_mem (int) ; 

hash_entry_vct_ptr htbl_vct_get_entry (void) {
  if (htbl_vct_free_entries == NULL) {
    if (1 <= htbl_vct_allocated_cnt && htbl_vct_allocated_cnt < 10000) {
      htbl_vct_init_mem (htbl_vct_allocated_cnt);
    } else {
      htbl_vct_init_mem (10000);
    }
  }

  assert (htbl_vct_free_entries != NULL);

  hash_entry_vct *res = htbl_vct_free_entries;
  htbl_vct_free_entries = htbl_vct_free_entries->next_entry;
  res->next_entry = NULL;

  return res;
}