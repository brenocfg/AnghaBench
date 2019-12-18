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

/* Variables and functions */
 int Q_limit ; 
 int Q_order ; 
 size_t* R ; 
 int R_cnt ; 
 scalar_t__ R_position ; 
 int R_tot ; 
 int* UserRate ; 
 size_t log_split_min ; 
 size_t log_split_mod ; 

void postprocess_res_std (void) {
  int i, j, k, t, r;
  if (R_position) { return; }
  switch (Q_order) {
  case -1:
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
    break;
  case 2:
    if (!R_cnt) { return; }
    for (k = R_cnt - 1; k > 0; k--) {
      t = R[k+1];
      R[2*k] = log_split_min + log_split_mod * R[1];
      R[2*k+1] = UserRate[R[1]];
      r = UserRate[t];
      i = 1;
      while (1) {
        j = 2*i;
        if (j > k) { break; }
        if (j < k && UserRate[R[j+1]] > UserRate[R[j]]) { j++; }
        if (r >= UserRate[R[j]]) { break; }
        R[i] = R[j];
        i = j;
      }
      R[i] = t;
    }
    R[0] = log_split_min + log_split_mod * R[1];
    R[1] = UserRate[R[1]];
    R_cnt *= 2;
    return;
  case -2:
    if (!R_cnt) { return; }
    for (k = R_cnt - 1; k > 0; k--) {
      t = R[k+1];
      R[2*k] = log_split_min + log_split_mod * R[1];
      R[2*k+1] = UserRate[R[1]];
      r = UserRate[t];
      i = 1;
      while (1) {
        j = 2*i;
        if (j > k) { break; }
        if (j < k && UserRate[R[j+1]] < UserRate[R[j]]) { j++; }
        if (r <= UserRate[R[j]]) { break; }
        R[i] = R[j];
        i = j;
      }
      R[i] = t;
    }
    R[0] = log_split_min + log_split_mod * R[1];
    R[1] = UserRate[R[1]];
    R_cnt *= 2;
    return;
  }      
  for (i = 0; i < R_cnt; i++) {
    R[i] = log_split_min + log_split_mod * R[i];
  }
}