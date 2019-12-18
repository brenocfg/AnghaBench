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
struct TYPE_2__ {int tot_buckets; } ;

/* Variables and functions */
 TYPE_1__* CC ; 
 int MAX_RES ; 
 void** Q ; 
 int QL ; 
 int* QN ; 
 int* R ; 
 int R_common_len ; 
 int* Rfirst ; 
 scalar_t__* Rlen ; 
 int /*<<< orphan*/  assert (int) ; 
 int split_factor ; 

__attribute__((used)) static void set_rlen () {
  int i, x;

  for (i = 0; i < CC->tot_buckets; i++) {
    Rlen[i] = 0;
    Rfirst[i] = -1;
  }


  split_factor = CC->tot_buckets ? CC->tot_buckets : 0;
  R[0] = 0x31303030;
  R_common_len = 1;
  for (i = QL-1; i >= 0; i--) {
    if (Q[2 * i + 1] < 0) {
      assert (R_common_len + 2 <= MAX_RES + 1);
      R[R_common_len++] = Q[2*i];
      R[R_common_len++] = Q[2*i+1];
    } else {
      x = Q[2 * i];

      if (x < 0) { x = -x; }
      x %= split_factor;

      if (x < CC->tot_buckets) {
        QN[i] = Rfirst[x];
        Rfirst[x] = i;
        Rlen[x] ++;
      }
    }
  }
}