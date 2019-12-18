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
struct kill {int how_often_num_allocated; int /*<<< orphan*/ * how_often_data; } ;
typedef  int /*<<< orphan*/  ev_uint32_t ;

/* Variables and functions */
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
kill_how_often_expand_to_hold_more(struct kill *msg)
{
  int tobe_allocated = msg->how_often_num_allocated;
  ev_uint32_t* new_data = NULL;
  tobe_allocated = !tobe_allocated ? 1 : tobe_allocated << 1;
  new_data = (ev_uint32_t*) realloc(msg->how_often_data,
      tobe_allocated * sizeof(ev_uint32_t));
  if (new_data == NULL)
    return -1;
  msg->how_often_data = new_data;
  msg->how_often_num_allocated = tobe_allocated;
  return 0;}