#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; int currId; int* rev; int /*<<< orphan*/  to; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ lookup_table ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t* htbl_find_or_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ltbl_check (TYPE_1__*) ; 
 int ltbl_get_to (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poly_h (int*,int) ; 
 int* qrealloc (int*,int,int) ; 

int ltbl_add (lookup_table *table, int key) {
  ltbl_check (table);

  assert (table->size > 0);

  int x;
  if ( (x = ltbl_get_to (table, key)) ) {
    return x;
  }

  if (table->currId >= table->size) {
    assert (table->currId == table->size);

    int len = table->size;

    table->size = table->currId * 2;
    table->rev = qrealloc (table->rev, sizeof (int) * table->size, sizeof (int) * len);
//    fprintf (stderr, "realloc done\n");
    assert (table->rev != NULL);
    assert (0 < table->size && table->size < 100000000);
    table->hash = poly_h (table->rev, table->size);
    memset (table->rev + len, 0, sizeof (int) * (table->size - len));
  }
  assert (table->currId < table->size);

  table->rev[table->currId] = key;
  //htbl_add (&(table->to), key, table->currId);
  *(htbl_find_or_create (&(table->to), key)) = table->currId;

  return table->currId++;
}