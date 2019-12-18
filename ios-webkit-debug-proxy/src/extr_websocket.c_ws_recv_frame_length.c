#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ws_t ;
typedef  int ws_state ;
typedef  TYPE_2__* ws_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  frame_length; scalar_t__ needed_length; } ;
struct TYPE_5__ {TYPE_2__* private_state; } ;

/* Variables and functions */
 int STATE_ERROR ; 
 int STATE_READ_FRAME ; 
 scalar_t__ ws_read_frame_length (TYPE_1__*) ; 

ws_state ws_recv_frame_length(ws_t self) {
  ws_private_t my = self->private_state;

  if (ws_read_frame_length(self)) {
    return STATE_ERROR;
  }
  if (my->needed_length || !my->frame_length) {
    return -1;
  }
  return STATE_READ_FRAME;
}