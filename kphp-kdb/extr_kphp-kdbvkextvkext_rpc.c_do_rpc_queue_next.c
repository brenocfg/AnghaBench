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
struct rpc_queue {TYPE_1__* completed; } ;
struct TYPE_2__ {long long x; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct rpc_queue*) ; 
 double precise_now ; 
 scalar_t__ rpc_poll (double) ; 

long long do_rpc_queue_next (struct rpc_queue *Q, double timeout) { /* {{{ */
  assert (Q);
  if (Q->completed) {
    //fprintf (stderr, "!");
    return Q->completed->x;    
  }
  do {
    if (rpc_poll (timeout) < 0) {
      return 0;
    }
    if (Q->completed) {
      return Q->completed->x;
    }    
  } while (precise_now < timeout);
  return 0;
}