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
 int incr_rate_new (long long,int,int) ; 

__attribute__((used)) static int incr_rate2 (long long item_id, int rate2_incr) {
  return incr_rate_new (item_id, 1, rate2_incr);
}