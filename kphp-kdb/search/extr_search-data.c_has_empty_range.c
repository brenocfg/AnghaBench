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
struct TYPE_2__ {scalar_t__ minr; scalar_t__ maxr; } ;

/* Variables and functions */
 TYPE_1__* Q_range ; 
 int n_ranges ; 

int has_empty_range () {
  int i = 0;
  for (i = 0; i < n_ranges; i++) {
    if (Q_range[i].minr > Q_range[i].maxr) {
      return 1;
    }
  }
  return 0;
}