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
struct run {int large_number_set; int /*<<< orphan*/  large_number_data; } ;
typedef  int /*<<< orphan*/  ev_uint64_t ;

/* Variables and functions */

int
run_large_number_assign(struct run *msg, const ev_uint64_t value)
{
  msg->large_number_set = 1;
  msg->large_number_data = value;
  return (0);
}