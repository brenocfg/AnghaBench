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
 scalar_t__ get_idx_item (long long) ; 
 struct item* get_item_f (long long,int /*<<< orphan*/ ) ; 
 int get_rate_item (struct item*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,struct item*,struct item*) ; 

int get_rates (int *rates, long long item_id) {
  struct item *I = get_item_f (item_id, ONLY_FIND);
  struct item *II = (struct item*) get_idx_item (item_id);

  vkprintf (2, "get_rates(%016llx): %p %p\n", item_id, I, II);

  if (II) {
    assert (!I);
    rates[0] = get_rate_item (II, 0);
    rates[1] = get_rate_item (II, 1);
    return 1;
  }
  if (!I || (I->extra & FLAG_DELETED)) {
    return 0;
  }
  rates[0] = get_rate_item (I, 0);
  rates[1] = get_rate_item (I, 1);
  return 1;
}