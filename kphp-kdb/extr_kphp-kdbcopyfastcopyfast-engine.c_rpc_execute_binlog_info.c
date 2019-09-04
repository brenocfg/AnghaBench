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
struct rpc_binlog_info {int /*<<< orphan*/  binlog_position; int /*<<< orphan*/  local_id; } ;
struct connection {int /*<<< orphan*/  last_response_time; } ;
struct TYPE_3__ {int /*<<< orphan*/  binlog_info_received; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relative_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  precise_now ; 
 int rpc_send_handshake_reject (struct connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  update_relatives_binlog_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verbosity ; 

int rpc_execute_binlog_info (struct connection *c, struct rpc_binlog_info *P, int len) {
  if (verbosity >= 2) {
    fprintf (stderr, "rpc_execute_binlog_info: remote_id = %lld, len = %d\n", P->local_id, len);
  }
  if (len != sizeof (struct rpc_binlog_info)) {
    return 0;
  }
  STATS->structured.binlog_info_received ++;
  if (!get_relative_by_id (P->local_id)) {
    return rpc_send_handshake_reject (c, P->local_id);
  }
  c->last_response_time = precise_now;
  update_relatives_binlog_position (P->local_id, P->binlog_position);
  return 0;
}