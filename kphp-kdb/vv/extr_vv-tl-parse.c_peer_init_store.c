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
struct tl_peer {int /*<<< orphan*/  PID; } ;
struct rpc_target {int dummy; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 struct connection* rpc_target_choose_connection (struct rpc_target*,int /*<<< orphan*/ *) ; 
 struct rpc_target* rpc_target_lookup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tl_store_init (struct connection*,long long) ; 

int peer_init_store (struct tl_peer *self, long long qid) {
  struct rpc_target *T = rpc_target_lookup (&self->PID);
  if (!T) {
    return -1;
  }
  struct connection *c = rpc_target_choose_connection (T, &self->PID);
  if (!c) {
    return -1;
  }
  tl_store_init (c, qid);
  return 0;
}