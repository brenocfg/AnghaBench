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
 int /*<<< orphan*/  set_rate_new (long long,int,int) ; 

__attribute__((used)) static int set_rates (long long item_id, int rate, int rate2) {
  if (!set_rate_new (item_id, 0, rate)) { return 0;}
  if (!set_rate_new (item_id, 1, rate2)) { return 0;}
  return 1;
}