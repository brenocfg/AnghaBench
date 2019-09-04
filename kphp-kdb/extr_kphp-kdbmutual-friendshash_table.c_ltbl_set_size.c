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
struct TYPE_3__ {int size; int /*<<< orphan*/  rev; int /*<<< orphan*/  hash; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ lookup_table ;

/* Variables and functions */
 int /*<<< orphan*/  htbl_set_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  poly_h (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qmalloc0 (int) ; 

void ltbl_set_size (lookup_table *table, int size) {
  htbl_set_size (&(table->to), size);
  table->rev = qmalloc0 (sizeof (int) * size);
  table->size = size;
  table->hash = poly_h (table->rev, table->size);
}