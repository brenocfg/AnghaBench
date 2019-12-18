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
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 long long GET_TIME_ID (int /*<<< orphan*/ ) ; 
 long long TIME_TABLE_RATIO_EXP ; 
 int /*<<< orphan*/  get_utime (int /*<<< orphan*/ ) ; 
 long long last_del_time ; 

long long get_time_gap (void) {
  return (GET_TIME_ID (get_utime (CLOCK_MONOTONIC)) - last_del_time) << TIME_TABLE_RATIO_EXP;
}