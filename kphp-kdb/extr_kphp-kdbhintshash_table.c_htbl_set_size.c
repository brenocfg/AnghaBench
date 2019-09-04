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
struct TYPE_3__ {int size; int /*<<< orphan*/ * h; } ;
typedef  TYPE_1__ hash_table ;
typedef  int /*<<< orphan*/  hash_entry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dl_malloc0 (int) ; 

void htbl_set_size (hash_table *table, int size) {
  assert (table->h == NULL);

  table->h = dl_malloc0 (sizeof (hash_entry *) * size);
  assert (table->h != NULL);

  table->size = size;
}