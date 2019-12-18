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
struct tree_rpc_target {struct rpc_target* x; } ;
struct TYPE_3__ {scalar_t__ ip; } ;
struct rpc_target {int /*<<< orphan*/  inbound_num; struct connection* last; struct connection* first; TYPE_1__ PID; } ;
struct connection {struct connection* next; struct connection* prev; scalar_t__ target; } ;
struct TYPE_4__ {TYPE_1__ remote_pid; } ;

/* Variables and functions */
 TYPE_2__* RPCS_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct rpc_target* rpc_target_alloc (TYPE_1__) ; 
 int /*<<< orphan*/  rpc_target_tree ; 
 scalar_t__ rpc_targets_cur_host ; 
 int /*<<< orphan*/  st_update_host () ; 
 struct tree_rpc_target* tree_lookup_rpc_target (int /*<<< orphan*/ ,struct rpc_target*) ; 

void rpc_target_insert_conn (struct connection *c) {
  if (c->target) { return; }
  st_update_host ();
  static struct rpc_target t;
  t.PID = RPCS_DATA(c)->remote_pid;
  if (rpc_targets_cur_host && !t.PID.ip) {
    t.PID.ip = rpc_targets_cur_host;
  }
  struct tree_rpc_target *T = tree_lookup_rpc_target (rpc_target_tree, &t);
  struct rpc_target *S = T ? T->x : 0;
  if (!S) {
    S = rpc_target_alloc (t.PID);
  }
  struct connection *d = S->first;
  while (d != (struct connection *)S) {
    if (d == c) {
      return;
    }
    d = d->next;
  }
  assert (!c->next);
  assert (!c->prev);
  c->next = (void *)S;
  c->prev = S->last;
  c->next->prev = c;
  c->prev->next = c;
  S->inbound_num ++;
}