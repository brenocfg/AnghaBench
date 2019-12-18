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
struct connection {int /*<<< orphan*/  status; int /*<<< orphan*/  last_query_sent_time; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rpc_ready ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_1__* RPCC_FUNC (struct connection*) ; 
 int /*<<< orphan*/  conn_wait_answer ; 
 int /*<<< orphan*/  precise_now ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 

int rpcc_connected_nohs (struct connection *c) {
  c->last_query_sent_time = precise_now;

  c->status = conn_wait_answer;
  if (RPCC_FUNC(c)->rpc_ready) {
    RPCC_FUNC(c)->rpc_ready (c);
  }

  return 0;
}