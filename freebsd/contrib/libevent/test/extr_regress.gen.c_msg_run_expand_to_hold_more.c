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
struct msg {int run_num_allocated; struct run** run_data; } ;

/* Variables and functions */
 scalar_t__ realloc (struct run**,int) ; 

__attribute__((used)) static int
msg_run_expand_to_hold_more(struct msg *msg)
{
  int tobe_allocated = msg->run_num_allocated;
  struct run** new_data = NULL;
  tobe_allocated = !tobe_allocated ? 1 : tobe_allocated << 1;
  new_data = (struct run**) realloc(msg->run_data,
      tobe_allocated * sizeof(struct run*));
  if (new_data == NULL)
    return -1;
  msg->run_data = new_data;
  msg->run_num_allocated = tobe_allocated;
  return 0;}