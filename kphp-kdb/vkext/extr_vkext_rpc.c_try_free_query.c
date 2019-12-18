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
 int /*<<< orphan*/  rpc_query_delete (struct rpc_query*) ; 
 struct rpc_query* rpc_query_get (long long) ; 

void try_free_query (long long qid) {
  struct rpc_query *q = rpc_query_get (qid);
  if (q) {
    rpc_query_delete (q);
  }
}