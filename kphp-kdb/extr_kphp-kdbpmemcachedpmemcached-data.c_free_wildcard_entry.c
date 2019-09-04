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
struct wildcard_entry {int key_len; int data_len; struct wildcard_entry* data; struct wildcard_entry* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  wildcard_cache_entries ; 
 int /*<<< orphan*/  wildcard_cache_memory ; 
 int /*<<< orphan*/  wildcard_del_use (struct wildcard_entry*) ; 
 int /*<<< orphan*/  zzfree (struct wildcard_entry*,int) ; 

void free_wildcard_entry (struct wildcard_entry *entry) {
  wildcard_del_use (entry);
  zzfree (entry->key, entry->key_len);
  zzfree (entry->data, entry->data_len);
  wildcard_cache_memory -= entry->key_len + entry->data_len + sizeof (struct wildcard_entry);
  zzfree (entry, sizeof (struct wildcard_entry));
  wildcard_cache_entries --;
}