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
struct TYPE_2__ {float val; } ;
typedef  TYPE_1__ score ;

/* Variables and functions */

int cmp_score_val (const void *a, const void *b) {
  float diff = ((score *)a)->val - ((score *)b)->val;
  return diff > 1e-9 ? -1 : diff < -1e-9;
}