#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ h_idx; } ;
struct udp_target {TYPE_1__ confirm_timer; TYPE_1__ rx_timer; TYPE_1__ tx_timer; scalar_t__ window_queue; scalar_t__ out_queue; int /*<<< orphan*/  sent; int /*<<< orphan*/  constructors; void* received_tree; void* confirm_tree; scalar_t__ hash; } ;
struct tmp_msg {TYPE_4__* msg; } ;
struct raw_message {int dummy; } ;
struct TYPE_8__ {struct raw_message raw; } ;
struct TYPE_7__ {struct raw_message x; } ;
struct TYPE_6__ {struct tmp_msg x; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_udp_msg_constructor ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 scalar_t__ queue_del_first_raw_message (scalar_t__) ; 
 scalar_t__ queue_del_first_tmp_msg (scalar_t__) ; 
 TYPE_3__* queue_get_first_raw_message (scalar_t__) ; 
 TYPE_2__* queue_get_first_tmp_msg (scalar_t__) ; 
 int /*<<< orphan*/  remove_event_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  rwm_free (struct raw_message*) ; 
 int /*<<< orphan*/  tree_act_udp_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_act_udp_msg_constructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* tree_clear_int (void*) ; 
 int /*<<< orphan*/  tree_clear_udp_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_clear_udp_msg_constructor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_delete_udp_target_by_hash (int /*<<< orphan*/ ,struct udp_target*) ; 
 int /*<<< orphan*/  udp_msg_free ; 
 int /*<<< orphan*/  udp_target_by_hash ; 
 int /*<<< orphan*/  zfree (struct udp_target*,int) ; 

void udp_target_free (struct udp_target *S) {
  if (S->hash) {
    udp_target_by_hash  = tree_delete_udp_target_by_hash (udp_target_by_hash, S);
  }
  S->confirm_tree = tree_clear_int (S->confirm_tree);
  S->received_tree = tree_clear_int (S->received_tree);
  tree_act_udp_msg_constructor (S->constructors, __clear_udp_msg_constructor);
  S->constructors = tree_clear_udp_msg_constructor (S->constructors);
  tree_act_udp_msg (S->sent, udp_msg_free);
  S->sent = tree_clear_udp_msg (S->sent);

  while (S->out_queue) {
    struct raw_message raw = queue_get_first_raw_message (S->out_queue)->x;
    rwm_free (&raw);
    S->out_queue = queue_del_first_raw_message (S->out_queue);
  }

  while (S->window_queue) {
    struct tmp_msg x = queue_get_first_tmp_msg (S->window_queue)->x;
    rwm_free (&x.msg->raw);
    free (x.msg);    
    S->window_queue = queue_del_first_tmp_msg (S->window_queue);
  }

  if (S->tx_timer.h_idx) {
    remove_event_timer (&S->tx_timer);
  }
  if (S->rx_timer.h_idx) {
    remove_event_timer (&S->rx_timer);
  }
  if (S->confirm_timer.h_idx) {
    remove_event_timer (&S->confirm_timer);
  }
  zfree (S, sizeof (*S));
}