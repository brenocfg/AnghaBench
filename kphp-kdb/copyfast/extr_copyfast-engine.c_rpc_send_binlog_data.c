#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_binlog_data {long long remote_id; long long binlog_position; int size; int /*<<< orphan*/  crc64; int /*<<< orphan*/  data; int /*<<< orphan*/  local_id; } ;
struct connection {int dummy; } ;
struct TYPE_4__ {int* total_sent_bytes_color; int /*<<< orphan*/  binlog_data_sent; int /*<<< orphan*/ * total_sent_num_color; } ;
struct TYPE_6__ {TYPE_1__ structured; } ;
struct TYPE_5__ {int link_color; } ;

/* Variables and functions */
 long long BINLOG_POSITION ; 
 long long MAX_SEND_LEN ; 
 int /*<<< orphan*/  NODE_ID ; 
 scalar_t__ Q ; 
 int /*<<< orphan*/  RPC_TYPE_BINLOG_DATA ; 
 TYPE_3__* STATS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ get_binlog_data (int /*<<< orphan*/ ,long long,int) ; 
 int /*<<< orphan*/  get_crc64 (long long) ; 
 TYPE_2__* get_relative_by_id (long long) ; 
 scalar_t__ rpc_create_query (struct rpc_binlog_data*,int,struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_query (struct rpc_binlog_data*,struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,long long) ; 

int rpc_send_binlog_data (struct connection *c, long long remote_id, long long pos) {
  vkprintf (2, "rpc_send_binlog_data: remote_id = %lld, pos = %lld\n", remote_id, pos);
  if (!remote_id) {
    return 0;
  }
  assert (pos < BINLOG_POSITION);
  int len = (BINLOG_POSITION - pos > MAX_SEND_LEN) ? MAX_SEND_LEN : BINLOG_POSITION - pos;
  struct rpc_binlog_data *T = (struct rpc_binlog_data *)Q;
  int llen = (len & 3) == 0 ? len : (len & ~3) + 4;
  assert (llen <= MAX_SEND_LEN);
  if (rpc_create_query (T, sizeof (struct rpc_binlog_data) + llen, c, RPC_TYPE_BINLOG_DATA) < 0) {
    return -1;
  }
  T->local_id = NODE_ID;
  T->remote_id = remote_id;
  T->binlog_position = pos;
  T->size = len;
  if (get_binlog_data (T->data, pos, len) < 0) {
    return 0;
  }
  T->crc64 = get_crc64 (pos);
  int color = get_relative_by_id (remote_id)->link_color;
  assert (0 <= color && color <= 2);
  STATS->structured.total_sent_num_color[color] ++;
  STATS->structured.total_sent_bytes_color[color] += len;
  STATS->structured.binlog_data_sent ++;
  return rpc_send_query (T, c);
}