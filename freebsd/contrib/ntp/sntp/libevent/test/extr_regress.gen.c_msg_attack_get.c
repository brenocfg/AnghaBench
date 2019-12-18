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
struct msg {int attack_set; struct kill* attack_data; } ;
struct kill {int dummy; } ;

/* Variables and functions */
 struct kill* kill_new () ; 

int
msg_attack_get(struct msg *msg, struct kill* *value)
{
  if (msg->attack_set != 1) {
    msg->attack_data = kill_new();
    if (msg->attack_data == NULL)
      return (-1);
    msg->attack_set = 1;
  }
  *value = msg->attack_data;
  return (0);
}