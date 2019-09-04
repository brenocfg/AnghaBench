#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lev_targ_global_click_stats {int len; TYPE_1__* stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  g; } ;
struct TYPE_3__ {long long views; long long clicks; } ;

/* Variables and functions */
 TYPE_2__ AdStats ; 
 int MAX_AD_VIEWS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static int set_global_click_stats (struct lev_targ_global_click_stats *E) {
  int i, len = E->len;
  assert (len == MAX_AD_VIEWS);
  long long sum_v = 0, sum_c = 0;
  for (i = 0; i < MAX_AD_VIEWS; i++) {
    assert (!(E->stats[i].views < 0 || E->stats[i].clicks < 0 || E->stats[i].clicks > E->stats[i].views || E->stats[i].views > (long long) 1e15));
    if (i > 0) {
      sum_v += E->stats[i].views;
      sum_c += E->stats[i].clicks;
      assert (sum_v <= (long long) 1e15);
    }
  }
  assert (sum_v == E->stats[0].views && sum_c == E->stats[0].clicks);
  memcpy (AdStats.g, E->stats, 16 * MAX_AD_VIEWS);
  return 1;
}