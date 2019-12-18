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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_prof ; 
 scalar_t__ opt_prof ; 
 int /*<<< orphan*/  prof_sample_threshold_update (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tsd_thread_prof_sample_event_init(tsd_t *tsd) {
	assert(config_prof && opt_prof);
	prof_sample_threshold_update(tsd);
}