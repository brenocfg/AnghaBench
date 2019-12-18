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
struct run {int other_numbers_length; int /*<<< orphan*/ * other_numbers_data; int /*<<< orphan*/  other_numbers_set; } ;
typedef  int /*<<< orphan*/  ev_uint32_t ;

/* Variables and functions */

int
run_other_numbers_get(struct run *msg, int offset,
    ev_uint32_t *value)
{
  if (!msg->other_numbers_set || offset < 0 || offset >= msg->other_numbers_length)
    return (-1);
  *value = msg->other_numbers_data[offset];
  return (0);
}