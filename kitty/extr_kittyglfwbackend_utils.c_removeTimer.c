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
typedef  int /*<<< orphan*/  id_type ;
typedef  int /*<<< orphan*/  EventLoopData ;

/* Variables and functions */
 int /*<<< orphan*/  removeX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timers ; 
 int /*<<< orphan*/  update_timers ; 

void
removeTimer(EventLoopData *eld, id_type timer_id) {
    removeX(timers, timer_id, update_timers);
}