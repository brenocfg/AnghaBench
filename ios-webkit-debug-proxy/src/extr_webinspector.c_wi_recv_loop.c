#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* wi_t ;
typedef  scalar_t__ wi_status ;
typedef  TYPE_3__* wi_private_t ;
struct TYPE_9__ {int has_length; size_t body_length; TYPE_1__* in; } ;
struct TYPE_8__ {scalar_t__ (* recv_packet ) (TYPE_2__*,char const*,int) ;TYPE_3__* private_state; } ;
struct TYPE_7__ {char* in_head; char* in_tail; } ;

/* Variables and functions */
 scalar_t__ WI_SUCCESS ; 
 scalar_t__ stub1 (TYPE_2__*,char const*,int) ; 
 scalar_t__ wi_parse_length (TYPE_2__*,char const*,size_t*) ; 

wi_status wi_recv_loop(wi_t self) {
  wi_private_t my = self->private_state;
  wi_status ret;
  const char *in_head = my->in->in_head;
  const char *in_tail = my->in->in_tail;
  while (1) {
    size_t in_length = in_tail - in_head;
    if (!my->has_length && in_length >= 4) {
      // can read body_length now
      size_t len;
      ret = wi_parse_length(self, in_head, &len);
      if (ret) {
        in_head += 4;
        break;
      }
      my->body_length = len;
      my->has_length = true;
      // don't advance in_head yet
    } else if (my->has_length && in_length >= my->body_length + 4) {
      // can read body now
      ret = self->recv_packet(self, in_head, my->body_length + 4);
      in_head += my->body_length + 4;
      my->has_length = false;
      my->body_length = 0;
      if (ret) {
        break;
      }
    } else {
      // need more input
      ret = WI_SUCCESS;
      break;
    }
  }
  my->in->in_head = in_head;
  return ret;
}