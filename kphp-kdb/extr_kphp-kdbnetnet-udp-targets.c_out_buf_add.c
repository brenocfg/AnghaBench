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
struct TYPE_2__ {int /*<<< orphan*/  h_idx; } ;
struct udp_target {int send_num; int max_confirmed; TYPE_1__ tx_timer; int /*<<< orphan*/  sent; } ;
struct udp_msg {int prev_next; scalar_t__ msg_num; int /*<<< orphan*/  raw; void* S; } ;
struct raw_message {scalar_t__ total_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  __out_buf_add (struct raw_message*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lrand48 () ; 
 int out_buf_next ; 
 scalar_t__ out_buf_next_last ; 
 int out_buf_prev ; 
 scalar_t__ out_buf_prev_last ; 
 void* out_buf_target ; 
 int /*<<< orphan*/  rwm_clone (int /*<<< orphan*/ *,struct raw_message*) ; 
 int /*<<< orphan*/  start_tx_timer (struct udp_target*) ; 
 int /*<<< orphan*/  tree_insert_udp_msg (int /*<<< orphan*/ ,struct udp_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,scalar_t__) ; 
 struct udp_msg* zmalloc (int) ; 

void out_buf_add (struct raw_message *raw) {
  assert (raw->total_bytes > 0);
  struct udp_msg *msg = zmalloc (sizeof (*msg));
  struct udp_target *S = out_buf_target;
  msg->S = out_buf_target;
  msg->msg_num = S->send_num ++;
  rwm_clone (&msg->raw, raw);
  int prev = (out_buf_prev_last ? out_buf_prev : 0);
  int next = out_buf_next_last ? out_buf_next : 0;
  msg->prev_next = ((prev * 1ll) << 32) + next;
  out_buf_prev_last = 0;
  out_buf_next_last = 0;
  S->sent = tree_insert_udp_msg (S->sent, msg, lrand48 ());
  vkprintf (4, "S->sent: added number %d\n", msg->msg_num);
  if (S->send_num - 2 == S->max_confirmed) {
    if (!S->tx_timer.h_idx) {
      start_tx_timer (S);
    }
  }

  __out_buf_add (raw, S->send_num - 1);
}