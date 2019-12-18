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
struct imc_events {struct imc_events* name; struct imc_events* scale; struct imc_events* unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct imc_events*) ; 

__attribute__((used)) static void imc_free_events(struct imc_events *events, int nr_entries)
{
	int i;

	/* Nothing to clean, return */
	if (!events)
		return;
	for (i = 0; i < nr_entries; i++) {
		kfree(events[i].unit);
		kfree(events[i].scale);
		kfree(events[i].name);
	}

	kfree(events);
}