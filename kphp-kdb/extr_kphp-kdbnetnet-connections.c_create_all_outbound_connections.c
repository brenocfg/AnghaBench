#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ refcnt; scalar_t__ ready_outbound_connections; scalar_t__ type; } ;

/* Variables and functions */
 TYPE_1__* Targets ; 
 int allocated_targets ; 
 scalar_t__ create_new_connections (TYPE_1__*) ; 
 int /*<<< orphan*/  get_utime_monotonic () ; 
 scalar_t__ ready_outbound_connections ; 
 scalar_t__ ready_targets ; 

int create_all_outbound_connections (void) {
  int count = 0, i;
  get_utime_monotonic ();
  ready_outbound_connections = ready_targets = 0;
  for (i = 0; i < allocated_targets; i++) {
    if (Targets[i].type && Targets[i].refcnt > 0) {
      count += create_new_connections (&Targets[i]);
      if (Targets[i].ready_outbound_connections) {
        ready_outbound_connections += Targets[i].ready_outbound_connections;
        ready_targets++;
      }
    }
  }
  return count;    
}