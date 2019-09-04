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
struct TYPE_4__ {int currId; int size; long long* rev; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ lookup_table ;

/* Variables and functions */
 long long* dl_realloc (long long*,int,int) ; 
 scalar_t__ htbl_find_or_create (int /*<<< orphan*/ *,long long) ; 
 int ltbl_get_to (TYPE_1__*,long long) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ltbl_add (lookup_table *table, long long key) {
  int x;

  if ( (x = ltbl_get_to (table, key)) ) {
    return x;
  }

  if (table->currId >= table->size) {
    int len = table->size;

    table->size = table->currId * 2;
//    fprintf (stderr, "%d %d %d\n", sizeof (long long) * table->size, len, table->size - len);
    table->rev = dl_realloc (table->rev, sizeof (long long) * table->size, sizeof (long long) * len);
//    fprintf (stderr, "realloc done\n");
    memset (table->rev + len, 0, sizeof (long long) * (table->size - len));
  }

  table->rev[table->currId] = key;
  //htbl_add (&(table->to), key, table->currId);
  *(long *)(htbl_find_or_create (&(table->to), key)) = table->currId;

  return table->currId++;
}