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
struct rpc_children_request {int /*<<< orphan*/  id; } ;
struct connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  children_requests_sent; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_ID ; 
 scalar_t__ Q ; 
 int /*<<< orphan*/  RPC_TYPE_CHILDREN_REQUEST ; 
 TYPE_2__* STATS ; 
 scalar_t__ rpc_create_query (struct rpc_children_request*,int,struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_query (struct rpc_children_request*,struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,struct connection*) ; 

int rpc_send_children_request (struct connection *c) {
  vkprintf (2, "rpc_send_children_request: c = %p\n", c);
  struct rpc_children_request *T = (struct rpc_children_request *)Q;
  if (rpc_create_query (T, sizeof (struct rpc_children_request), c, RPC_TYPE_CHILDREN_REQUEST) < 0) {
    return -1;
  }
  T->id = NODE_ID;
  STATS->structured.children_requests_sent ++;
  return rpc_send_query (T, c);
}