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
struct views_clicks_ll {long long views; long long clicks; } ;
struct lev_targ_global_click_stats {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_GLOBAL_CLICK_STATS ; 
 int MAX_AD_VIEWS ; 
 struct lev_targ_global_click_stats* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct views_clicks_ll*,int) ; 
 int set_global_click_stats (struct lev_targ_global_click_stats*) ; 
 int /*<<< orphan*/  stderr ; 

int do_set_global_click_stats (int len, struct views_clicks_ll *A) {
  int i;
  fprintf (stderr, "do_set_global_click_stats(%d)\n", len);
  if (len != MAX_AD_VIEWS) {
    return 0;
  }
  long long sum_v = 0, sum_c = 0;
  for (i = 0; i < MAX_AD_VIEWS; i++) {
    if (A[i].views < 0 || A[i].clicks < 0 || A[i].clicks > A[i].views || A[i].views > (long long) 1e15) {
      return 0;
    }
    if (i > 0) {
      sum_v += A[i].views;
      sum_c += A[i].clicks;
      if (sum_v > (long long) 1e15) {
        return 0;
      }
    }
  }
  if (sum_v != A[0].views || sum_c != A[0].clicks) {
    return 0;
  }
  struct lev_targ_global_click_stats *E = alloc_log_event (LEV_TARG_GLOBAL_CLICK_STATS, len * 16 + 8, len);
  memcpy (E->stats, A, len * 16);
  return set_global_click_stats (E);
}