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
typedef  scalar_t__ ll ;
struct TYPE_2__ {scalar_t__ h; } ;
typedef  TYPE_1__ entry_t ;

/* Variables and functions */

int entry_t_cmp (const void *a, const void *b) {
  ll x = ((entry_t *)a)->h, y = ((entry_t *)b)->h;
  if (x < y) {
    return -1;
  }
  if (x > y) {
    return 1;
  }
  return 0;
}