#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct item {long long item_id; int extra; } ;

/* Variables and functions */
 int FLAG_DELETED ; 
 long long ITEMS_HASH_PRIME ; 
 struct item** Items ; 
 scalar_t__ MAX_ITEMS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_item (struct item*,long long) ; 
 int /*<<< orphan*/  del_items ; 
 int /*<<< orphan*/  fits (long long) ; 
 scalar_t__ tot_items ; 
 struct item* ztmalloc (int) ; 

__attribute__((used)) static struct item *get_item_f (long long item_id, int force) {
  int h1, h2;
  struct item *C;
  if (item_id <= 0 || !fits (item_id)) { return 0; }
  h1 = item_id % ITEMS_HASH_PRIME;
  h2 = 1 + (item_id % (ITEMS_HASH_PRIME - 1));
  int first_deleted = -1;
  while ((C = Items[h1]) != 0) {
    if (C->item_id == item_id) {
      return C;
    }
    if (first_deleted < 0 && (C->extra & FLAG_DELETED)) { first_deleted = h1; }
    h1 += h2;
    if (h1 >= ITEMS_HASH_PRIME) { h1 -= ITEMS_HASH_PRIME; }
  }
  if (!force || tot_items >= MAX_ITEMS) { return 0; }
  if (first_deleted >= 0) {
    C = Items[first_deleted];
    del_items--;
  } else {
    C = ztmalloc (sizeof (struct item));
    if (!C) { return C; }
    Items[h1] = C;
    tot_items++;
  }
  assert (create_item (C, item_id));
  return C;
}