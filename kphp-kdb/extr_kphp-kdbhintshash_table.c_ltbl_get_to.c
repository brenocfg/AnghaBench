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
struct TYPE_3__ {int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ lookup_table ;
typedef  scalar_t__ changes ;

/* Variables and functions */
 scalar_t__* htbl_find (int /*<<< orphan*/ *,long long) ; 

int ltbl_get_to (lookup_table *table, long long key) {
  changes *x = htbl_find (&(table->to), key);

  if (x != NULL) {
    //return -(long)(*x) / 2;
    return (long)(*x);
  }

  return 0;
}