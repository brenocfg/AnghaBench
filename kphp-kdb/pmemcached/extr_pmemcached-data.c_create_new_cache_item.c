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
struct TYPE_2__ {int data_len; } ;
struct entry {int key_len; int index_entry; scalar_t__ hash_entry; int /*<<< orphan*/  key; TYPE_1__ data; } ;

/* Variables and functions */
 int cache_size ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  zzmalloc (int) ; 

void create_new_cache_item (struct entry* entry, const char *key, int key_len) {
  entry->key_len = key_len;
  entry->key = zzmalloc (key_len * sizeof(char));
  entry->index_entry = -1;
  entry->data.data_len = -2;
  if (key_len >= 0) {
    memcpy (entry->key, key, key_len * sizeof(char));
  }  
  entry->hash_entry = 0;
  cache_size += key_len * sizeof (char);
}