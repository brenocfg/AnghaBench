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
 int incr_rate_item (struct item*,int,int) ; 

__attribute__((used)) static int incr_rate_new (long long item_id, int p, int rate_incr) {
  struct item *I = get_item_f (item_id, ONLY_FIND);
  struct item *II = (struct item*) get_idx_item (item_id);
  if (II) {
    assert (!I);
    return incr_rate_item (II, p, rate_incr);
  }
  if (!I || (I->extra & FLAG_DELETED)) {
    return 0;
  }
  return incr_rate_item (I, p, rate_incr);
}