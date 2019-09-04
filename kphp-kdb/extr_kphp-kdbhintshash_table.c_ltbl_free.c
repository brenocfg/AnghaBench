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
struct TYPE_3__ {int size; int currId; int /*<<< orphan*/ * rev; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ lookup_table ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  htbl_no_free (int /*<<< orphan*/ *) ; 

void ltbl_free (lookup_table *table) {
  htbl_no_free (&(table->to));
  dl_free (table->rev, sizeof (long long) * table->size);

  table->rev = NULL;
  table->size = 0;
  table->currId = 1;
}