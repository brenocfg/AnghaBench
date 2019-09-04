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
struct tree_rpc_target {struct rpc_target* x; } ;
struct process_id {scalar_t__ ip; } ;
struct rpc_target {struct process_id PID; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct process_id*) ; 
 int /*<<< orphan*/  rpc_target_tree ; 
 scalar_t__ rpc_targets_cur_host ; 
 int /*<<< orphan*/  st_update_host () ; 
 struct tree_rpc_target* tree_lookup_rpc_target (int /*<<< orphan*/ ,struct rpc_target*) ; 

struct rpc_target *rpc_target_lookup (struct process_id *PID) {
  assert (PID);
  st_update_host ();
  static struct rpc_target t;
  t.PID = *PID;
  if (rpc_targets_cur_host && !t.PID.ip) {
    t.PID.ip = rpc_targets_cur_host;
  }
  struct tree_rpc_target *T = tree_lookup_rpc_target (rpc_target_tree, &t);
  return T ? T->x : 0;
}