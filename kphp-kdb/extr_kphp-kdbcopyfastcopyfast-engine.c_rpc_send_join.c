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
struct rpc_join {int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  binlog_position; scalar_t__ id; int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
struct connection {int /*<<< orphan*/  our_ip; } ;
struct TYPE_3__ {int /*<<< orphan*/  joined_sent; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINLOG_POSITION ; 
 scalar_t__ CC ; 
 scalar_t__ CLUSTER_ID ; 
 scalar_t__* Clusters ; 
 scalar_t__ NODE_ID ; 
 int /*<<< orphan*/  PROTOCOL_VERSION ; 
 scalar_t__ Q ; 
 int /*<<< orphan*/  RPC_TYPE_JOIN ; 
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  host ; 
 int max_cluster ; 
 int /*<<< orphan*/  port ; 
 scalar_t__ rpc_create_query (struct rpc_join*,int,struct connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_send_query (struct rpc_join*,struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,struct connection*) ; 

int rpc_send_join (struct connection *c) {    
  vkprintf (2, "rpc_send_join: c = %p\n", c);
  int i;
  for (i = 0; i < max_cluster; i++) if (Clusters[i]) {
    struct rpc_join *T = (struct rpc_join *)Q;
    if (rpc_create_query (T, sizeof (struct rpc_join), c, RPC_TYPE_JOIN) < 0) {
      return -1;
    }
    CC = Clusters[i];
    T->host = c->our_ip;
    host = c->our_ip;
    T->port = port;
    T->id = NODE_ID ? NODE_ID : CLUSTER_ID;
    T->binlog_position = BINLOG_POSITION;
    T->protocol_version = PROTOCOL_VERSION;
    STATS->structured.joined_sent++;
    rpc_send_query (T, c);
  }
  return 0;
}