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
 long long* index_cnt ; 
 scalar_t__* index_deleted ; 
 int index_size ; 

int index_get_idx (long long count_id) {
  int l = -1;
  int r = index_size;
  while (r - l > 1) {
    int x = (r + l)>>1;
    if (index_cnt[x] < count_id) {
      l = x;
    } else {
      r = x;
    }
  }
  l++;
  if (l == index_size || index_cnt[l] != count_id || index_deleted[l]) {
    return index_size;
  } else {
    return l;
  }
}