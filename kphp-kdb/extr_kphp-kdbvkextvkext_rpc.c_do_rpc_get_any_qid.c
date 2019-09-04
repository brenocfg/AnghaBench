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
struct TYPE_2__ {long long x; } ;

/* Variables and functions */
 double precise_now ; 
 TYPE_1__* query_completed ; 
 int /*<<< orphan*/  rpc_poll (double) ; 

long long do_rpc_get_any_qid (double timeout) { /* {{{ */
  if (query_completed) {
    return query_completed->x;
  }
  if (timeout > precise_now) {
    rpc_poll (timeout);
    if (query_completed) {
      return query_completed->x;
    }
  }
  return -1;
}