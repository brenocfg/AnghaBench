#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; TYPE_2__** h; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ hash_table ;
typedef  TYPE_2__* hash_entry_ptr ;
struct TYPE_9__ {struct TYPE_9__* next_entry; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  htbl_check (TYPE_1__*) ; 
 TYPE_2__* htbl_free_entries ; 
 int /*<<< orphan*/  poly_h (TYPE_2__**,int) ; 
 int /*<<< orphan*/  qfree (TYPE_2__**,int) ; 

void htbl_free (hash_table *table) {
  htbl_check (table);
  if (table == NULL) {
    return;
  }

  int n = table->size, i;
  hash_entry_ptr *h = table->h;
  for (i = 0; i < n; i++) {
    hash_entry_ptr curr = h[i];
    if (curr != NULL) {
      while (curr->next_entry != NULL) {
        curr->data = 0;
        curr = curr->next_entry;
      }
      curr->data = 0;
      curr->next_entry = htbl_free_entries;
      htbl_free_entries = h[i];
      h[i] = NULL;
    }
  }

  qfree (table->h, sizeof (hash_entry_ptr) * table->size);
  table->h = NULL;
  table->size = 0;
  table->hash = poly_h (table->h, table->size);
}