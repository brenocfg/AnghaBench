#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {long long item_id; } ;
typedef  TYPE_1__ item_t ;
typedef  int get_item_f_mode ;

/* Variables and functions */
#define  ADD_NOT_FOUND_ITEM 129 
 long long ITEMS_HASH_PRIME ; 
 int /*<<< orphan*/  ITEM_DELETED (TYPE_1__*) ; 
 TYPE_1__** Items ; 
 int /*<<< orphan*/  MAX_ITEMS ; 
#define  ONLY_FIND 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tot_freed_deleted_items ; 
 int /*<<< orphan*/  tot_items ; 
 int /*<<< orphan*/  zfree (TYPE_1__*,int) ; 
 TYPE_1__* zmalloc0 (int) ; 

__attribute__((used)) static item_t *get_item_f (long long item_id, get_item_f_mode force) {
  int h1, h2;
  item_t *C, *D;
  if (item_id <= 0) { return 0; }
  h1 = item_id % ITEMS_HASH_PRIME;
  h2 = 1 + (item_id % (ITEMS_HASH_PRIME - 1));

  switch (force) {
    case ONLY_FIND:
      while ((D = Items[h1]) != 0) {
        if (D->item_id == item_id) {
          return D;
        }
        h1 += h2;
        if (h1 >= ITEMS_HASH_PRIME) { h1 -= ITEMS_HASH_PRIME; }
      }
      return 0;
    case ADD_NOT_FOUND_ITEM:
      while ((D = Items[h1]) != 0) {
        if (ITEM_DELETED(D)) {
          break;
        }
        h1 += h2;
        if (h1 >= ITEMS_HASH_PRIME) { h1 -= ITEMS_HASH_PRIME; }
      }
    if (tot_items >= MAX_ITEMS) { return 0; }
    C = zmalloc0 (sizeof (item_t));
    if (!C) { return C; }
    if (D) {
      zfree (D, sizeof (item_t));
      tot_freed_deleted_items++;
    }
    else { tot_items++; }
    Items[h1] = C;
    C->item_id = item_id;
    return C;
  }
  assert (0);
  return 0;
}