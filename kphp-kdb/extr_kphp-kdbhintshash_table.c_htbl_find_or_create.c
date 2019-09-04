#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int size; TYPE_2__** h; } ;
typedef  TYPE_1__ hash_table ;
struct TYPE_6__ {long long key; int /*<<< orphan*/  data; struct TYPE_6__* next_entry; } ;
typedef  TYPE_2__ hash_entry ;
typedef  int /*<<< orphan*/  changes ;

/* Variables and functions */
 int /*<<< orphan*/  CHG_INIT (int /*<<< orphan*/ ) ; 
 TYPE_2__* htbl_get_entry () ; 

changes *htbl_find_or_create (hash_table *table, long long key) {
  int i = (unsigned int)key % table->size;

  hash_entry *curr = table->h[i];
  while (curr != NULL) {
    if (curr->key == key) {
      return &(curr->data);
    }
    curr = curr->next_entry;
  }

  curr = htbl_get_entry();
  curr->key = key;
  CHG_INIT(curr->data);
  curr->next_entry = table->h[i];
  table->h[i] = curr;

  return &(curr->data);
}