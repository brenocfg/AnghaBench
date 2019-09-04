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
 int* Q ; 
 int* QN ; 
 int Q_ul_size ; 
 int Q_userlist ; 
 int* Qf ; 
 scalar_t__* Qs ; 
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_raw_data (int*,int) ; 

int work_userlist (void) {
  Q_userlist = 1;
  int n = tl_fetch_int ();
  Q_ul_size = n;
  int N = CC->tot_buckets;
  int i;
  for (i = 0; i < N; i++) {
    Qf[i] = -1;
    Qs[i] = 0;
  }
  if (n <= 0) {
    return 4;
  } else {
    tl_fetch_raw_data (Q, 4 * n);
    for (i = n - 1; i >= 0; i--) {
      int m = Q[i] % N;
      if (m < 0) { m = -m; }
      QN[i] = Qf[m];
      Qf[m] = i;
      Qs[m] ++;
    }
    return 4 + 4 * n;
  }
}