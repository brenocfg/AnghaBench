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
struct rpc_binlog_request {scalar_t__ binlog_position; int /*<<< orphan*/  local_id; } ;
struct connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  binlog_request_received; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 scalar_t__ BINLOG_POSITION ; 
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relative_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_send_binlog_data (struct connection*,int /*<<< orphan*/ ,scalar_t__) ; 
 int rpc_send_handshake_reject (struct connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpc_execute_binlog_request (struct connection *c, struct rpc_binlog_request *P, int len) {
  if (verbosity >= 2) {
    fprintf (stderr, "rpc_execute_binlog_request: remote_id = %lld, len = %d\n", P->local_id, len);
  }
  if (len != sizeof (struct rpc_binlog_request)) {
    return 0;
  }
  STATS->structured.binlog_request_received ++;
  if (!get_relative_by_id (P->local_id)) {
    return rpc_send_handshake_reject (c, P->local_id);
  }
  if (P->binlog_position >= BINLOG_POSITION) {
    return 0;
  }
  rpc_send_binlog_data (c, P->local_id, P->binlog_position);
  return 0;
}