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
struct tree_rpc_target {struct rpc_target* x; } ;
struct TYPE_2__ {int ip; int /*<<< orphan*/  port; } ;
struct rpc_target {TYPE_1__ PID; } ;
struct conn_target {int custom_field; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_target_tree ; 
 int rpc_targets_cur_host ; 
 int /*<<< orphan*/  st_update_host () ; 
 struct tree_rpc_target* tree_lookup_rpc_target (int /*<<< orphan*/ ,struct rpc_target*) ; 

struct rpc_target *rpc_target_lookup_target (struct conn_target *targ) {
  if (targ->custom_field == -1) {
    return 0;
  }
  st_update_host ();
  static struct rpc_target t;
  t.PID.ip = targ->custom_field; //ntohl (targ->target.s_addr);
  if (t.PID.ip == 0x7f000001) {
    t.PID.ip = 0;
  }
  if (rpc_targets_cur_host && !t.PID.ip) {
    t.PID.ip = rpc_targets_cur_host;
  }
  t.PID.port = targ->port;
  struct tree_rpc_target *T = tree_lookup_rpc_target (rpc_target_tree, &t);
  return T ? T->x : 0;
}