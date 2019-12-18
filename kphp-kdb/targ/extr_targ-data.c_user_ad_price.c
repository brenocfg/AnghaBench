#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct user {int /*<<< orphan*/  active_ads; } ;
struct TYPE_2__ {double expected_gain; } ;

/* Variables and functions */
 double CTR_GAIN_PRICE_MULTIPLIER ; 
 int GSORT_HEAP_SIZE ; 
 TYPE_1__* H ; 
 int HN ; 
 int MAX_USERS ; 
 struct user** User ; 
 int /*<<< orphan*/  build_user_ad_heap (struct user*,int) ; 

int user_ad_price (int uid, int position) {
  if (uid < 0 || uid >= MAX_USERS || position <= 0 || position >= GSORT_HEAP_SIZE) {
    return 0;
  }

  struct user *U = User[uid];
  if (!U || !U->active_ads) {
    return 0;
  }

  build_user_ad_heap (U, position);
  if (HN < position) {
    return 0;
  }

  return (int) (H[1].expected_gain * CTR_GAIN_PRICE_MULTIPLIER + 0.5);
}