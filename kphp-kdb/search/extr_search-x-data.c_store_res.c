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
struct item {int /*<<< orphan*/  item_id; } ;
struct TYPE_2__ {int minr; int maxr; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 scalar_t__ Q_hash_group_mode ; 
 scalar_t__ Q_limit ; 
 TYPE_1__* Q_range ; 
 struct item** R ; 
 double* RR ; 
 scalar_t__ R_cnt ; 
 int /*<<< orphan*/  R_tot ; 
 double evaluate_rating (struct item*,double) ; 
 int get_rate_item_fast (struct item*,int /*<<< orphan*/ ) ; 
 int n_ranges ; 
 int /*<<< orphan*/  store_res_group_mode (struct item*,double) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,double) ; 

int store_res (struct item *I, double w) {
  vkprintf (3, "store_res (item_id = %lld, w = %.10lf\n", I->item_id, w);
  if (w < 1e-9) { return 1; }
  int i, j = 0;
  for (i = 0; i < n_ranges; i++) {
    int r0 = get_rate_item_fast (I, Q_range[i].idx);
    if (r0 < Q_range[i].minr || r0 > Q_range[i].maxr) {
      return 1;
    }
  }

  R_tot++;
  if (Q_limit <= 0) {
    return 1;
  }

  double r = evaluate_rating (I, w);

  if (Q_hash_group_mode) {
    store_res_group_mode (I, r);
    return 1;
  }

  if (R_cnt == Q_limit) {
    if (RR[1] <= r) {
      return 1;
    }
    i = 1;
    while (1) {
      j = i*2;
      if (j > R_cnt) { break; }
      if (j < R_cnt) {
        if (RR[j+1] > RR[j]) {
          j++;
        }
      }
      if (RR[j] <= r) { break; }
      R[i] = R[j];
      RR[i] = RR[j];
      i = j;
    }
    R[i] = I;
    RR[i] = r;
  } else {
    i = ++R_cnt;
    while (i > 1) {
      j = (i >> 1);
      if (RR[j] >= r) { break; }
      R[i] = R[j];
      RR[i] = RR[j];
      i = j;
    }
    R[i] = I;
    RR[i] = r;
  }
  return 1;
}