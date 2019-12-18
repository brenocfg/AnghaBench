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
struct rpc_join_ack {int id; } ;
struct connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  join_ack_received; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC ; 
 int CLUSTER_ID ; 
 int CLUSTER_MASK ; 
 int ID_MASK ; 
 int NODE_ID ; 
 TYPE_2__* STATS ; 
 int rpc_send_children_request (struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,...) ; 

int rpc_execute_join_ack (struct connection *c, struct rpc_join_ack *P, int len) {
  vkprintf (2, "rpc_execute_join_ack: len = %d\n", len);
  if (len != sizeof (struct rpc_join_ack)) {
    return 0;
  }
  STATS->structured.join_ack_received++;
  NODE_ID = P->id;
  vkprintf (6, "%p %lld %lld\n", CC, NODE_ID, CLUSTER_ID);
  if (!(NODE_ID & ID_MASK) || (NODE_ID & CLUSTER_MASK) != CLUSTER_ID) {
    NODE_ID = CLUSTER_ID;
    return 0;
  }
  return rpc_send_children_request (c);
}