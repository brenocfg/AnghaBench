#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpc_children_request {int /*<<< orphan*/  id; } ;
struct connection {int dummy; } ;
struct TYPE_2__ {scalar_t__ protocol_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int get_node_idx (int /*<<< orphan*/ ) ; 
 TYPE_1__* nodes ; 
 int rpc_send_children (struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_children_old (struct connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpc_execute_children_request (struct connection *c, struct rpc_children_request *P, int len) {
  if (verbosity >= 2) {
    fprintf (stderr, "rpc_execute_children_request: len = %d\n", len);
  }
  if (len != sizeof (struct rpc_children_request)) {
    return 0;
  }
  int x = get_node_idx (P->id);
  if (nodes[x].protocol_version == 0) {
    return rpc_send_children_old (c, P->id);
  } else {
    return rpc_send_children (c, P->id);
  }
}