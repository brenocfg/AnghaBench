#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long long key_hash; int key_len; int next_entry; scalar_t__ exp_time; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 size_t GET_ENTRY_ID (long long) ; 
 int /*<<< orphan*/  del_entry (int) ; 
 TYPE_1__* entry_buffer ; 
 scalar_t__ get_utime (int /*<<< orphan*/ ) ; 
 int* hash_st ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 

int get_entry (const char *key, int key_len, long long hash) {
  int i = hash_st[GET_ENTRY_ID (hash)];

  while (i != -1 && (hash != entry_buffer[i].key_hash || key_len != entry_buffer[i].key_len ||
                     strncmp (key, entry_buffer[i].key, key_len) != 0)) {
    i = entry_buffer[i].next_entry;
  }

  if (i != -1 && entry_buffer[i].exp_time < get_utime (CLOCK_MONOTONIC)) {
    del_entry (i);
    i = -1;
  }

  return i;
}