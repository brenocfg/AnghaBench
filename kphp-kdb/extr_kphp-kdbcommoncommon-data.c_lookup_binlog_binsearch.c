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
struct TYPE_2__ {long long time; } ;

/* Variables and functions */
 TYPE_1__* fbd_data ; 

__attribute__((used)) static inline int lookup_binlog_binsearch (long long binlog_time, int a, int b) {
  int c;
  --a;
  while (b - a > 1) {
    c = (a + b) >> 1;
    if (fbd_data[c].time < binlog_time) {
      a = c;
    } else {
      b = c;
    }
  }
  return b;
}