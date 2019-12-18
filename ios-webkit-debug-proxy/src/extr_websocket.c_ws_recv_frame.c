#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ws_t ;
typedef  int ws_state ;
typedef  TYPE_3__* ws_private_t ;
typedef  scalar_t__ uint8_t ;
struct TYPE_11__ {scalar_t__ begin; scalar_t__ tail; } ;
struct TYPE_10__ {scalar_t__ frame_length; scalar_t__ continued_opcode; TYPE_7__* data; TYPE_1__* in; scalar_t__ needed_length; } ;
struct TYPE_9__ {scalar_t__ (* on_frame ) (TYPE_2__*,int,scalar_t__,int,scalar_t__,scalar_t__,int*) ;TYPE_3__* private_state; } ;
struct TYPE_8__ {scalar_t__ in_tail; scalar_t__ in_head; } ;

/* Variables and functions */
 scalar_t__ OPCODE_CLOSE ; 
 scalar_t__ OPCODE_CONTINUATION ; 
 int STATE_CLOSED ; 
 int STATE_ERROR ; 
 int STATE_READ_FRAME_LENGTH ; 
 int /*<<< orphan*/  cb_clear (TYPE_7__*) ; 
 scalar_t__ stub1 (TYPE_2__*,int,scalar_t__,int,scalar_t__,scalar_t__,int*) ; 
 scalar_t__ ws_read_frame (TYPE_2__*,int*,scalar_t__*,int*) ; 

ws_state ws_recv_frame(ws_t self) {
  ws_private_t my = self->private_state;

  if (my->needed_length || !my->frame_length ||
      my->in->in_tail - my->in->in_head < my->frame_length) {
    return -1;
  }

  bool is_fin;
  uint8_t opcode;
  bool is_masking;
  if (ws_read_frame(self, &is_fin, &opcode, &is_masking)) {
    return STATE_ERROR;
  }

  bool should_keep = 1;
  if (self->on_frame(self, is_fin, opcode, is_masking,
        my->data->begin, my->data->tail - my->data->begin,
        &should_keep)) {
    return STATE_ERROR;
  }
  if (is_fin || !should_keep) {
    cb_clear(my->data);
  }

  if (is_fin) {
    my->continued_opcode = 0;
  } else if (opcode != OPCODE_CONTINUATION) {
    my->continued_opcode = opcode;
  }

  if (opcode == OPCODE_CLOSE) {
    return STATE_CLOSED;
  }
  return STATE_READ_FRAME_LENGTH;
}