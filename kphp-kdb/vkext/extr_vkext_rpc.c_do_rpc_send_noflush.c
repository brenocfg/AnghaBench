#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rpc_query {int /*<<< orphan*/  qid; } ;
struct rpc_connection {int /*<<< orphan*/  servers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 struct rpc_query* rpc_query_alloc (double) ; 
 int /*<<< orphan*/  rpc_query_delete (struct rpc_query*) ; 
 int /*<<< orphan*/  rpc_send ; 
 scalar_t__ rpc_write (struct rpc_connection*,int /*<<< orphan*/ ,double) ; 

struct rpc_query *do_rpc_send_noflush (struct rpc_connection *c, double timeout) { /* {{{ */
  ADD_CNT (rpc_send);
  START_TIMER (rpc_send);
  if (!c || !c->servers) {
    END_TIMER (rpc_send);
    return 0;
  }

  
  struct rpc_query *q = rpc_query_alloc (timeout);
  if (!q) {
    END_TIMER (rpc_send);
    return 0;
  }
  if (rpc_write (c, q->qid, timeout) < 0) {
//    rpc_server_failure (c->server);
    rpc_query_delete (q);
    END_TIMER (rpc_send);
    return 0;
  }

  END_TIMER (rpc_send); 
  return q;
}