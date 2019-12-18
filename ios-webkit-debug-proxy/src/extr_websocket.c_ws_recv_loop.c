#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ws_t ;
typedef  int /*<<< orphan*/  ws_status ;
typedef  scalar_t__ ws_state ;
typedef  TYPE_3__* ws_private_t ;
struct TYPE_11__ {TYPE_1__* in; scalar_t__ state; } ;
struct TYPE_10__ {TYPE_3__* private_state; } ;
struct TYPE_9__ {scalar_t__ in_tail; scalar_t__ in_head; } ;

/* Variables and functions */
#define  STATE_CLOSED 134 
#define  STATE_ERROR 133 
#define  STATE_KEEP_ALIVE 132 
#define  STATE_READ_FRAME 131 
#define  STATE_READ_FRAME_LENGTH 130 
#define  STATE_READ_HTTP_HEADERS 129 
#define  STATE_READ_HTTP_REQUEST 128 
 int /*<<< orphan*/  WS_ERROR ; 
 int /*<<< orphan*/  WS_SUCCESS ; 
 scalar_t__ ws_recv_frame (TYPE_2__*) ; 
 scalar_t__ ws_recv_frame_length (TYPE_2__*) ; 
 scalar_t__ ws_recv_headers (TYPE_2__*) ; 
 scalar_t__ ws_recv_request (TYPE_2__*) ; 

ws_status ws_recv_loop(ws_t self) {
  ws_private_t my = self->private_state;
  while (1) {
    ws_state new_state;
    switch (my->state) {
      case STATE_READ_HTTP_REQUEST:
        new_state = ws_recv_request(self);
        break;

      case STATE_READ_HTTP_HEADERS:
        new_state = ws_recv_headers(self);
        break;

      case STATE_KEEP_ALIVE:
        // discard non-ws content
        my->in->in_tail = my->in->in_head;
        new_state = -1;
        break;

      case STATE_READ_FRAME_LENGTH:
        new_state = ws_recv_frame_length(self);
        break;

      case STATE_READ_FRAME:
        new_state = ws_recv_frame(self);
        break;

      case STATE_CLOSED:
      case STATE_ERROR:
      default:
        return WS_ERROR;
    }
    if (new_state < 0) {
      return WS_SUCCESS;
    }
    my->state = new_state;
    if (new_state == STATE_CLOSED || new_state == STATE_ERROR) {
      return WS_ERROR;
    }
    if (my->in->in_tail == my->in->in_head) {
      return WS_SUCCESS;
    }
  }
}