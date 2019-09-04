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
struct related_binlog {int flags; } ;

/* Variables and functions */
 struct related_binlog* LR ; 
 int LRF_MASTER ; 
 size_t classify_slave (struct related_binlog*) ; 
 int local_rbs ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_rb_stats (struct related_binlog*) ; 

void compute_slaves_stats (int slave_cnt[4]) {
  int i;
  memset (slave_cnt, 0, 16);
  for (i = 0; i < local_rbs; i++) {
    struct related_binlog *R = &LR[i];
    if (!(R->flags & LRF_MASTER)) {
      slave_cnt[classify_slave (R)]++;
    }
    update_rb_stats (R);
  }
}