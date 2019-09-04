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
struct udp_target {scalar_t__ state; } ;
struct tl_peer {int /*<<< orphan*/  PID; } ;

/* Variables and functions */
 int /*<<< orphan*/  tl_store_init_raw_msg_keep_error (struct udp_target*,long long) ; 
 scalar_t__ udp_failed ; 
 struct udp_target* udp_target_lookup (int /*<<< orphan*/ *) ; 

int peer_udp_init_store_keep_error (struct tl_peer *self, long long qid) {
  struct udp_target *S = udp_target_lookup (&self->PID);
  if (!S || S->state == udp_failed) {
    return -1;
  }
  tl_store_init_raw_msg_keep_error (S, qid);
  return 0;
}