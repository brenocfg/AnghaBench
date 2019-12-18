#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_handshake_accept {int /*<<< orphan*/  binlog_position; int /*<<< orphan*/  local_id; } ;
struct connection {int /*<<< orphan*/  last_response_time; } ;
struct TYPE_3__ {int /*<<< orphan*/  handshake_accept_received; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_relative_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  precise_now ; 
 int rpc_send_handshake_reject (struct connection*,int /*<<< orphan*/ ) ; 
 int update_relatives_binlog_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int) ; 

int rpc_execute_handshake_accept (struct connection *c, struct rpc_handshake_accept *P, int len) {
  vkprintf (2, "rpc_execute_handshake_accept: remote_id = %lld, len = %d\n", P->local_id, len);
  if (len != sizeof (struct rpc_handshake_accept)) {
    return 0;
  }
  STATS->structured.handshake_accept_received ++;
  if (!get_relative_by_id (P->local_id)) {
    return rpc_send_handshake_reject (c, P->local_id);
  }
  c->last_response_time = precise_now;
  assert (update_relatives_binlog_position (P->local_id, P->binlog_position) >= 1);
  return 0;
}