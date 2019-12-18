#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct udp_socket {struct udp_message* recv_queue_last; struct udp_message* recv_queue; scalar_t__ recv_queue_len; scalar_t__ recv_queue_bytes; TYPE_1__* type; int /*<<< orphan*/  send_queue_bytes; int /*<<< orphan*/  send_queue_len; int /*<<< orphan*/  fd; } ;
struct udp_message {int flags; struct udp_message* next; } ;
struct TYPE_2__ {int (* process_error_msg ) (struct udp_socket*,struct udp_message*) ;int (* process_msg ) (struct udp_socket*,struct udp_message*) ;} ;

/* Variables and functions */
 int UMF_ERROR ; 
 int /*<<< orphan*/  free_udp_message (struct udp_message*) ; 
 int stub1 (struct udp_socket*,struct udp_message*) ; 
 int stub2 (struct udp_socket*,struct udp_message*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int udp_process_incoming (struct udp_socket *u) {
  vkprintf (2, "udp_process_incoming(%d): %d messages in receive queue (%d bytes); %d messages in send queue (%d bytes)\n", u->fd, u->recv_queue_len, u->recv_queue_bytes, u->send_queue_len, u->send_queue_bytes);
  struct udp_message *msg_cur, *msg_next = u->recv_queue;
  if (!msg_next) {
    return 0;
  }
  do {
    msg_cur = msg_next;
    msg_next = msg_next->next;
    msg_cur->next = 0;
    int res;
    if (msg_cur->flags & UMF_ERROR) {
      res = u->type->process_error_msg (u, msg_cur);
    } else {
      res = u->type->process_msg (u, msg_cur); // >0 -- just remove from queue, <= 0 -- free as well
    }
    if (res <= 0) {
      free_udp_message (msg_cur);
    }
  } while (msg_next);
  u->recv_queue_bytes = u->recv_queue_len = 0;
  u->recv_queue = u->recv_queue_last = 0;
  return 0;
}