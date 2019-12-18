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
struct TYPE_4__ {int /*<<< orphan*/  active_ads; int /*<<< orphan*/  user_id; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int /*<<< orphan*/  AdSpace ; 
 unsigned int GSORT_HEAP_SIZE ; 
 scalar_t__ HN ; 
 int /*<<< orphan*/  __build_heap_generation ; 
 int __build_heap_multiplier ; 
 int __gsort_limit ; 
 TYPE_1__* __user ; 
 int /*<<< orphan*/  __user_id ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  heap_push_user_ad ; 
 int intree_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lrand48 () ; 

__attribute__((used)) static int build_user_ad_heap (user_t *U, int limit) {
  assert (limit && (unsigned) limit < GSORT_HEAP_SIZE);
  __gsort_limit = limit;
  __user_id = U->user_id;
  __user = U;
  __build_heap_generation++;
  __build_heap_multiplier = (lrand48 () + 0x40000000) | 1;
  HN = 0;
  return intree_traverse (AdSpace, U->active_ads, heap_push_user_ad);
}