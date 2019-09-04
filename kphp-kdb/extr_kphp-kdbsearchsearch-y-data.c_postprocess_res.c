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
typedef  int /*<<< orphan*/  item_t ;

/* Variables and functions */
 int FLAG_REVERSE_SEARCH ; 
 scalar_t__ MAX_RATES ; 
 int Q_limit ; 
 int Q_order ; 
 scalar_t__ Q_type ; 
 int /*<<< orphan*/ ** R ; 
 int R_cnt ; 
 int R_tot ; 
 int /*<<< orphan*/  heap_sort_res () ; 

__attribute__((used)) static void postprocess_res (void) {
  int i, k;
  item_t *t;
  if (Q_type == MAX_RATES) { //sort by id
    if (Q_order & FLAG_REVERSE_SEARCH) {
      k = R_cnt - 1;
      for (i = 0; i < k - i; i++) {
        t = R[k-i];  R[k-i] = R[i];  R[i] = t;
      }
      if (R_tot >= Q_limit) {
        k = R_cnt + Q_limit - 1;
        for (i = R_cnt; i < k - i; i++) {
          t = R[k-i];  R[k-i] = R[i];  R[i] = t;
        }
        R_cnt = Q_limit;
      }
    }
    return;
  }

  if (!R_cnt) { return; }
  heap_sort_res ();
}