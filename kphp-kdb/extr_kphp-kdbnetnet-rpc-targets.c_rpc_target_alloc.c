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
struct process_id {int dummy; } ;
struct rpc_target {scalar_t__ inbound_num; struct connection* last; struct connection* first; scalar_t__ target; struct process_id PID; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  rpc_target_tree ; 
 int /*<<< orphan*/  tree_insert_rpc_target (int /*<<< orphan*/ ,struct rpc_target*,int /*<<< orphan*/ ) ; 
 struct rpc_target* zmalloc (int) ; 

struct rpc_target *rpc_target_alloc (struct process_id PID) {
  struct rpc_target *S = zmalloc (sizeof (*S));
  S->PID = PID;
  S->target = 0;
  S->first = S->last = (struct connection *)S;
  S->inbound_num = 0;
  rpc_target_tree = tree_insert_rpc_target (rpc_target_tree, S, lrand48 ());
  return S;
}