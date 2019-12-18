#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int data_len; int delay; scalar_t__ flags; scalar_t__ data; } ;
struct entry {int timestamp; int index_entry; TYPE_2__ data; scalar_t__ allocated_here; TYPE_1__* hash_entry; } ;
struct TYPE_3__ {int data_len; int exp_time; int timestamp; scalar_t__ flags; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_size ; 
 int /*<<< orphan*/  zzfree (scalar_t__,int) ; 

inline void cache_assign_data (struct entry *entry) {
  if (entry->hash_entry) {
    if (entry->allocated_here) {
      zzfree (entry->data.data, entry->data.data_len + 1);
      cache_size -= entry->data.data_len + 1;
      entry->allocated_here = 0;
    }
    entry->data.data_len = entry->hash_entry->data_len;
    entry->data.data = entry->hash_entry->data;
    entry->data.flags = entry->hash_entry->flags;
    entry->data.delay = entry->hash_entry->exp_time;
    entry->timestamp = entry->hash_entry->timestamp;
  } else if (entry->index_entry != 1) {
    if (entry->allocated_here) {
      zzfree (entry->data.data, entry->data.data_len + 1);
      cache_size -= entry->data.data_len + 1;
      entry->allocated_here = 0;
    }
    if (entry->index_entry == 0) {
      entry->data.data_len = -1;
    } else {
      entry->data.data_len = -2;
    }
    entry->data.data = 0;
    entry->data.flags = 0;
    entry->data.delay = -1;
    entry->timestamp = -2;
  }
}