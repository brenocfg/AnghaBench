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
struct TYPE_2__ {int idx; int /*<<< orphan*/  maxr; int /*<<< orphan*/  minr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 int MAX_RATES ; 
 TYPE_1__* Q_range ; 
 int n_ranges ; 

__attribute__((used)) static int find_range_idx (int sm) {
  int i;
  for (i = 0; i < n_ranges; i++) {
    if (Q_range[i].idx == sm) {
      return i;
    }
  }
  if (n_ranges >= MAX_RATES) {
    return -1;
  }
  Q_range[n_ranges].minr = INT_MIN;
  Q_range[n_ranges].maxr = INT_MAX;
  Q_range[n_ranges].idx = sm;
  return n_ranges++;
}