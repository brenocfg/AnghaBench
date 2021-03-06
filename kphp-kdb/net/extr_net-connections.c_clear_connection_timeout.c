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
struct TYPE_2__ {scalar_t__ wakeup_time; } ;
struct connection {TYPE_1__ timer; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_ALARM ; 
 int remove_event_timer (TYPE_1__*) ; 

int clear_connection_timeout (struct connection *c) {
  c->flags &= ~C_ALARM;
  c->timer.wakeup_time = 0;
  return remove_event_timer (&c->timer);
}