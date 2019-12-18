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
 int /*<<< orphan*/ * R ; 
 int R_cnt ; 
 int lrand48 () ; 
 int /*<<< orphan*/  scan_targ_aud_user (int /*<<< orphan*/ ) ; 

void postprocess_res_targ_aud (void) {
  int N = R_cnt;
  if (Q_limit > N) {
    Q_limit = N;
  }
  long M = Q_limit, i;
  for (i = 0; (int) i < R_cnt; i++) {
    if (lrand48() % N < M) {
      M--;
      scan_targ_aud_user (R[i]);
    }
    N--;
  }
}