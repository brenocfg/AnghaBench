#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vector ;
struct TYPE_4__ {unsigned int size; TYPE_2__** h; } ;
typedef  TYPE_1__ hash_table_vct ;
struct TYPE_5__ {long long key; struct TYPE_5__* next_entry; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ hash_entry_vct ;

/* Variables and functions */

vector *htbl_vct_find (hash_table_vct *table, long long key) {
  int i = (unsigned int)key % table->size;

  hash_entry_vct *curr = table->h[i];
  while (curr != NULL) {
    if (curr->key == key) {
      return &(curr->data);
    }
    curr = curr->next_entry;
  }

  return NULL;
}