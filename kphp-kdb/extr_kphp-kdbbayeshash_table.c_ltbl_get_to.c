#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ lookup_table ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int* htbl_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ltbl_check (TYPE_1__*) ; 

int ltbl_get_to (lookup_table *table, int key) {
  ltbl_check (table);
  assert (table->size > 0);

  int *x = htbl_find (&(table->to), key);

  if (x != NULL) {
    return *x;
  }

  return 0;
}