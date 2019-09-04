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
struct rpc_binlog_info {long long remote_id; int /*<<< orphan*/  binlog_position; int /*<<< orphan*/  local_id; } ;
struct connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  binlog_info_sent; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINLOG_POSITION ; 
 int /*<<< orphan*/  NODE_ID ; 
 scalar_t__ Q ; 
 int /*<<< orphan*/  RPC_TYPE_BINLOG_INFO ; 
 TYPE_2__* STATS ; 
 scalar_t__ rpc_create_query (struct rpc_binlog_info*,int,struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_query (struct rpc_binlog_info*,struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long) ; 

int rpc_send_binlog_info (struct connection *c, long long remote_id) {
  vkprintf (2, "rpc_send_binlog_info: remote_id = %lld\n", remote_id);
  if (!remote_id) {
    return 0;
  }
  struct rpc_binlog_info *T = (struct rpc_binlog_info *)Q;
  if (rpc_create_query (T, sizeof (struct rpc_binlog_info), c, RPC_TYPE_BINLOG_INFO) < 0) {
    return -1;
  }
  T->local_id = NODE_ID;
  T->remote_id = remote_id;
  T->binlog_position = BINLOG_POSITION;
  STATS->structured.binlog_info_sent ++;
  return rpc_send_query (T, c);
}