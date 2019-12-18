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
struct device {int dummy; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deferred_trigger_count ; 
 int /*<<< orphan*/  driver_deferred_probe_add (struct device*) ; 
 int /*<<< orphan*/  driver_deferred_probe_trigger () ; 

__attribute__((used)) static void driver_deferred_probe_add_trigger(struct device *dev,
					      int local_trigger_count)
{
	driver_deferred_probe_add(dev);
	/* Did a trigger occur while probing? Need to re-trigger if yes */
	if (local_trigger_count != atomic_read(&deferred_trigger_count))
		driver_deferred_probe_trigger();
}