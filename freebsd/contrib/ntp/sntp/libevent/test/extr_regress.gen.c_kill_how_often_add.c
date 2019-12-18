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
struct kill {scalar_t__ how_often_length; scalar_t__ how_often_num_allocated; int how_often_set; int /*<<< orphan*/ * how_often_data; } ;
typedef  int /*<<< orphan*/  ev_uint32_t ;

/* Variables and functions */
 scalar_t__ kill_how_often_expand_to_hold_more (struct kill*) ; 

ev_uint32_t *
kill_how_often_add(struct kill *msg, const ev_uint32_t value)
{
  if (++msg->how_often_length >= msg->how_often_num_allocated) {
    if (kill_how_often_expand_to_hold_more(msg)<0)
      goto error;
  }
  msg->how_often_data[msg->how_often_length - 1] = value;
  msg->how_often_set = 1;
  return &(msg->how_often_data[msg->how_often_length - 1]);
error:
  --msg->how_often_length;
  return (NULL);
}