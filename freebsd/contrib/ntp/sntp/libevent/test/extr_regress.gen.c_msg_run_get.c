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
struct run {int dummy; } ;
struct msg {int run_length; struct run** run_data; int /*<<< orphan*/  run_set; } ;

/* Variables and functions */

int
msg_run_get(struct msg *msg, int offset,
    struct run* *value)
{
  if (!msg->run_set || offset < 0 || offset >= msg->run_length)
    return (-1);
  *value = msg->run_data[offset];
  return (0);
}