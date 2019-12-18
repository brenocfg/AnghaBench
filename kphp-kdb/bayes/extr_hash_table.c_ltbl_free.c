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
struct TYPE_4__ {int size; int currId; int /*<<< orphan*/ * rev; int /*<<< orphan*/  hash; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ lookup_table ;

/* Variables and functions */
 int /*<<< orphan*/  htbl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltbl_check (TYPE_1__*) ; 
 int /*<<< orphan*/  poly_h (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qfree (int /*<<< orphan*/ *,int) ; 

void ltbl_free (lookup_table *table) {
  ltbl_check (table);
  htbl_free (&(table->to));
  qfree (table->rev, sizeof (int) * table->size);

  table->rev = NULL;
  table->size = 0;
  table->currId = 1;
  table->hash = poly_h (table->rev, table->size);
}