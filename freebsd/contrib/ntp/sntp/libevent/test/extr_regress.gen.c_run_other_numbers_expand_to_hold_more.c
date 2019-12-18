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
struct run {int other_numbers_num_allocated; int /*<<< orphan*/ * other_numbers_data; } ;
typedef  int /*<<< orphan*/  ev_uint32_t ;

/* Variables and functions */
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
run_other_numbers_expand_to_hold_more(struct run *msg)
{
  int tobe_allocated = msg->other_numbers_num_allocated;
  ev_uint32_t* new_data = NULL;
  tobe_allocated = !tobe_allocated ? 1 : tobe_allocated << 1;
  new_data = (ev_uint32_t*) realloc(msg->other_numbers_data,
      tobe_allocated * sizeof(ev_uint32_t));
  if (new_data == NULL)
    return -1;
  msg->other_numbers_data = new_data;
  msg->other_numbers_num_allocated = tobe_allocated;
  return 0;}