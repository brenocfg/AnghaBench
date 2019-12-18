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
struct rpc_query {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 int /*<<< orphan*/  active_queries ; 
 int /*<<< orphan*/  hash_delete_rpc_query (int /*<<< orphan*/ *,struct rpc_query*) ; 
 int /*<<< orphan*/  remove_event_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_query_hash_table ; 
 int /*<<< orphan*/  zfree (struct rpc_query*,int) ; 

void default_on_free (struct rpc_query *q) {
  remove_event_timer (&q->ev); 
  hash_delete_rpc_query (&rpc_query_hash_table, q);
  zfree (q, sizeof (*q));
  active_queries --;
}