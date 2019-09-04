#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; TYPE_2__** h; } ;
typedef  TYPE_1__ hash_table_vct ;
typedef  TYPE_2__* hash_entry_vct_ptr ;
struct TYPE_7__ {struct TYPE_7__* next_entry; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (TYPE_2__**,int) ; 
 TYPE_2__* htbl_vct_free_entries ; 
 int /*<<< orphan*/  vct_free (int /*<<< orphan*/ *) ; 

void htbl_vct_free (hash_table_vct *table) {
  if (table == NULL) {
    return;
  }

  int n = table->size, i;
  hash_entry_vct_ptr *h = table->h;
  for (i = 0; i < n; i++) {
    hash_entry_vct_ptr curr = h[i];
    if (curr != NULL) {
      while (curr->next_entry != NULL) {
        vct_free (&curr->data);
        curr = curr->next_entry;
      }
      vct_free (&curr->data);
      curr->next_entry = htbl_vct_free_entries;
      htbl_vct_free_entries = h[i];
      h[i] = NULL;
    }
  }

  dl_free (table->h, sizeof (hash_entry_vct_ptr) * table->size);
  table->h = NULL;
  table->size = 0;
}