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
struct connection {scalar_t__ Tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  free_all_buffers (scalar_t__) ; 
 scalar_t__ verbosity ; 

void net_readvar_callback (struct connection *c) {
  //  int i, j;

  assert (c->Tmp);
//  Msg = (raw_message_t *) c->Tmp->start;

//  Msg->data[Msg->len] = 0;

  if (verbosity > 0) {
//    fprintf (stderr, "(%d) got new message %d of user %d, len %d : %-40s...\n",
//       Msg->no_reply, Msg->message_id, Msg->user_id, Msg->len, Msg->data);
  }

  free_all_buffers (c->Tmp);
  c->Tmp = 0;

//  if (!Msg->no_reply) {
//    write_out (&c->Out, "STORED\r\n", 8);
//  }


}