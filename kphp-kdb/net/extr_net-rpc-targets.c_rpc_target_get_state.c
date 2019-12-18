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
struct rpc_target {struct connection* first; TYPE_1__* target; } ;
struct process_id {int dummy; } ;
struct connection {int unreliability; struct connection* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  remote_pid; } ;
struct TYPE_3__ {struct connection* first_conn; } ;

/* Variables and functions */
 TYPE_2__* RPCS_DATA (struct connection*) ; 
 int cr_ok ; 
 int cr_stopped ; 
 int matches_pid (int /*<<< orphan*/ *,struct process_id*) ; 
 int server_check_ready (struct connection*) ; 

int rpc_target_get_state (struct rpc_target *S, struct process_id *PID) {
  if (!S) {
    return 0;
  }
  int best = -1;
  int u = 10000;
  int r;
  struct connection *c;
  if (S->target) {
    for (c = S->target->first_conn; c != (struct connection *) (S->target); c = c->next) {
      r = server_check_ready (c);
      if (r == cr_ok) {
        if (!PID || matches_pid (&RPCS_DATA(c)->remote_pid, PID) >= 1) {
          return 1;
        }
      } else if (r == cr_stopped && c->unreliability < u) {
        if (!PID || matches_pid (&RPCS_DATA(c)->remote_pid, PID) >= 1) {
          best = 0;
        }
      }
    }
  }
  for (c = S->first; c != (struct connection *) (S); c = c->next) {
    r = server_check_ready (c);
    if (r == cr_ok) {
      if (!PID || matches_pid (&RPCS_DATA(c)->remote_pid, PID) >= 1) {
        return 1;
      }
    } else if (r == cr_stopped && c->unreliability < u) {
      if (!PID || matches_pid (&RPCS_DATA(c)->remote_pid, PID) >= 1) {
        best = 0;
      }
    }
  }
  return best;
}