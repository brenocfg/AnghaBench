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
typedef  int ll ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ engine_id ; 
 int engine_n ; 
 scalar_t__ get_utime (int /*<<< orphan*/ ) ; 

ll get_next_alias (void) {
  static ll st = -1;
  if (st == -1) {
    st = ((ll)get_utime(CLOCK_REALTIME) + 1001) * 1000000;
    st /= engine_n;
    st *= engine_n;
    st += engine_id;
  }
  st += engine_n;
  assert (st > 1000000000);
  return st;
}