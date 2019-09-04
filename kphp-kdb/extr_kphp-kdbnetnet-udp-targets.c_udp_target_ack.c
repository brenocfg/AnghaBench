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
struct udp_target {int send_num; int max_confirmed; scalar_t__ window_size; int flags; int /*<<< orphan*/  sent; int /*<<< orphan*/  last_ack; scalar_t__ resend_state; } ;
struct udp_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ START_WINDOW_SIZE ; 
 int UDP_WAIT ; 
 struct udp_target* __S ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  precise_now ; 
 int /*<<< orphan*/  start_tx_timer (struct udp_target*) ; 
 int /*<<< orphan*/  stop_tx_timer (struct udp_target*) ; 
 int /*<<< orphan*/  tree_delete_udp_msg (int /*<<< orphan*/ ,struct udp_msg*) ; 
 struct udp_msg** tree_lookup_value_udp_msg (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  udp_msg_confirm_free (struct udp_msg*) ; 
 int /*<<< orphan*/  udp_target_restart_send (struct udp_target*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

void udp_target_ack (struct udp_target *S, int x) {
  if (x >= S->send_num) {
    return;
  }
  if (x > S->max_confirmed) {
    stop_tx_timer (S);
    S->max_confirmed = x;
    assert (x < S->send_num);
    if (x != S->send_num - 1) {
      start_tx_timer (S);
    }
    S->resend_state = 0;
  }
  S->last_ack = precise_now;
  struct udp_msg **M = tree_lookup_value_udp_msg (S->sent, (void *)&x);
  if (!M) {
    return;
  }
  struct udp_msg *msg = *M;
  S->sent = tree_delete_udp_msg (S->sent, msg);
  vkprintf (4, "S->sent: delete message %d\n", x);
  __S = S;
  udp_msg_confirm_free (msg);
  if (S->window_size <= START_WINDOW_SIZE && (S->flags & UDP_WAIT)) {
    udp_target_restart_send (S);
  }
}