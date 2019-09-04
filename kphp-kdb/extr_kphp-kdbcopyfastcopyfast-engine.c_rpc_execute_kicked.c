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
struct rpc_kicked {int dummy; } ;
struct connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kicked_received; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_ID ; 
 int /*<<< orphan*/  NODE_ID ; 
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  clear_all_children_connections () ; 
 int rpc_send_join (struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int rpc_execute_kicked (struct connection *c, struct rpc_kicked *P, int len) {
  vkprintf (2, "rpc_kicked: len = %d\n", len);
  if (len != sizeof (struct rpc_kicked)) {
    return 0;
  }
  STATS->structured.kicked_received ++;
  NODE_ID = CLUSTER_ID;
  clear_all_children_connections ();
  return rpc_send_join (c);
}