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
struct TYPE_2__ {int data_len; scalar_t__ data; } ;
struct entry {int key_len; scalar_t__ key; TYPE_1__ data; scalar_t__ allocated_here; } ;

/* Variables and functions */
 int cache_size ; 
 int /*<<< orphan*/  zzfree (scalar_t__,int) ; 

void free_cache_item (struct entry *entry) {
  if (entry->key) {
    zzfree (entry->key, entry->key_len * sizeof (char));
    cache_size -= entry->key_len * sizeof (char);
    if (entry->allocated_here) {
      zzfree (entry->data.data, entry->data.data_len + 1);
      entry->allocated_here = 0;
      cache_size -= entry->data.data_len + 1;
    }
  }
  entry->key = 0;
}