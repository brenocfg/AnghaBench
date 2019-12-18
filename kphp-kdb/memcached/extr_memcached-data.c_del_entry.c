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
struct TYPE_3__ {int next_entry; int /*<<< orphan*/  key_hash; scalar_t__ data_len; int /*<<< orphan*/  data; scalar_t__ key_len; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 size_t GET_ENTRY_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int* buffer_stack ; 
 int /*<<< orphan*/  buffer_stack_size ; 
 int /*<<< orphan*/  del_entry_time (int) ; 
 int /*<<< orphan*/  del_entry_used (int) ; 
 TYPE_1__* entry_buffer ; 
 int* hash_st ; 
 int /*<<< orphan*/  zzfree (int /*<<< orphan*/ ,scalar_t__) ; 

void del_entry (int x) {
  hash_entry_t *entry = &entry_buffer[x];

  del_entry_used (x);
  del_entry_time (x);

  zzfree (entry->key, entry->key_len + 1);
  zzfree (entry->data, entry->data_len + 1);

  int *i = &hash_st[GET_ENTRY_ID (entry->key_hash)];

  while (*i != x && *i != -1) {
    i = &(entry_buffer[*i].next_entry);
  }

  assert (*i == x);

  *i = entry->next_entry;

  buffer_stack[buffer_stack_size++] = x;
}