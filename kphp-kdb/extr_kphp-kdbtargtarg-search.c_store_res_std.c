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
 int R_position ; 
 int /*<<< orphan*/  R_tot ; 
 int* UserRate ; 
 int user_ad_price (int,int) ; 

void store_res_std (int uid) {
  int i, j, r;
  R_tot++;
  if (R_position > 0) {
    r = user_ad_price (uid, R_position);
    if (r >= Q_limit) { 
      r = Q_limit - 1; 
    } else if (r < 0) {
      r = 0;
    }
    R[r]++;
    return;
  } else if (R_position == (-1 << 31)) {
    return;
  }
  if (Q_limit <= 0) { return; }
  switch (Q_order) {
  case 0:
  case 1:
  default:
    if (R_cnt < Q_limit) {
      R[R_cnt++] = uid;
    }
    break;
  case -1:
    if (R_cnt == Q_limit) { R_cnt = 0; }
    R[R_cnt++] = uid;
    break;
  case -2:
    r = UserRate[uid];
    if (R_cnt == Q_limit) {
      if (UserRate[R[1]] >= r) { return; }
      i = 1;
      while (1) {
        j = i*2;
        if (j > R_cnt) { break; }
        if (j < R_cnt && UserRate[R[j+1]] < UserRate[R[j]]) { j++; }
        if (UserRate[R[j]] >= r) { break; }
        R[i] = R[j];
        i = j;
      }
      R[i] = uid;
    } else {
      i = ++R_cnt;
      while (i > 1) {
        j = (i >> 1);
        if (UserRate[R[j]] <= r) { break; }
        R[i] = R[j];
        i = j;
      }
      R[i] = uid;
    }
    break;
  case 2:
    r = UserRate[uid];
    if (R_cnt == Q_limit) {
      if (UserRate[R[1]] <= r) { return; }
      i = 1;
      while (1) {
        j = i*2;
        if (j > R_cnt) { break; }
        if (j < R_cnt && UserRate[R[j+1]] > UserRate[R[j]]) { j++; }
        if (UserRate[R[j]] <= r) { break; }
        R[i] = R[j];
        i = j;
      }
      R[i] = uid;
    } else {
      i = ++R_cnt;
      while (i > 1) {
        j = (i >> 1);
        if (UserRate[R[j]] >= r) { break; }
        R[i] = R[j];
        i = j;
      }
      R[i] = uid;
    }
    break;
  }    
}