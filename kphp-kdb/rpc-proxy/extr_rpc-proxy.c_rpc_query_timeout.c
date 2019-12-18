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
struct rpc_query {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_rpc_query (struct rpc_query*) ; 
 int query_on_alarm (struct rpc_query*) ; 

__attribute__((used)) static void rpc_query_timeout (struct rpc_query *q) {
  int t = query_on_alarm (q);
  if (t > 0) { return; }
/*  if (q->type.on_alarm) {
    q->type.on_alarm (q);
  } else {
    default_on_alarm (q);
  }*/
  delete_rpc_query (q);
}