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
struct msg {int run_length; int /*<<< orphan*/ * run_data; scalar_t__ run_set; int /*<<< orphan*/  attack_data; scalar_t__ attack_set; int /*<<< orphan*/  to_name_set; int /*<<< orphan*/  from_name_set; } ;

/* Variables and functions */
 int kill_complete (int /*<<< orphan*/ ) ; 
 int run_complete (int /*<<< orphan*/ ) ; 

int
msg_complete(struct msg *msg)
{
  if (!msg->from_name_set)
    return (-1);
  if (!msg->to_name_set)
    return (-1);
  if (msg->attack_set && kill_complete(msg->attack_data) == -1)
    return (-1);
  {
    int i;
    for (i = 0; i < msg->run_length; ++i) {
      if (msg->run_set && run_complete(msg->run_data[i]) == -1)
        return (-1);
    }
  }
  return (0);
}