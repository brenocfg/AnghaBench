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
struct shutdown_trigger {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ON_PANIC_STR ; 
 int /*<<< orphan*/  ON_RESTART_STR ; 
 int /*<<< orphan*/  disabled_wait () ; 
 int /*<<< orphan*/  smp_stop_cpu () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_run(struct shutdown_trigger *trigger)
{
	if (strcmp(trigger->name, ON_PANIC_STR) == 0 ||
	    strcmp(trigger->name, ON_RESTART_STR) == 0)
		disabled_wait();
	smp_stop_cpu();
}