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
struct nicvf {int /*<<< orphan*/  stats_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct nicvf*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  nicvf_update_stats (struct nicvf*) ; 

__attribute__((used)) static void
nicvf_tick_stats(void *arg)
{
	struct nicvf *nic;

	nic = (struct nicvf *)arg;

	/* Read the statistics */
	nicvf_update_stats(nic);

	callout_reset(&nic->stats_callout, hz, nicvf_tick_stats, nic);
}