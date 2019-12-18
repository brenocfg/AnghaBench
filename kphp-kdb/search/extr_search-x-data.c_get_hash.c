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
struct item {int extra; } ;

/* Variables and functions */
 int FLAG_DELETED ; 
 int /*<<< orphan*/  ONLY_FIND ; 
 int /*<<< orphan*/  assert (int) ; 
 long long get_hash_item (struct item*) ; 
 scalar_t__ get_idx_item (long long) ; 
 struct item* get_item_f (long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,struct item*,struct item*) ; 

int get_hash (long long *hash, long long item_id) {
  struct item *I = get_item_f (item_id, ONLY_FIND);
  struct item *II = (struct item*) get_idx_item (item_id);

  vkprintf (2, "get_hash(%016llx): %p %p\n", item_id, I, II);

  if (II) {
    assert (!I);
    *hash = get_hash_item (II);
    return 1;
  }

  if (!I || (I->extra & FLAG_DELETED)) {
    return 0;
  }
  *hash = get_hash_item (I);
  return 1;
}