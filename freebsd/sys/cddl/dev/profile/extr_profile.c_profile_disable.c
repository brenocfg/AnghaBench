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
struct TYPE_3__ {scalar_t__ prof_kind; int /*<<< orphan*/  prof_cyclic; } ;
typedef  TYPE_1__ profile_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ PROF_PROFILE ; 
 scalar_t__ PROF_TICK ; 
 int callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profile_disable_omni (TYPE_1__*) ; 

__attribute__((used)) static void
profile_disable(void *arg, dtrace_id_t id, void *parg)
{
	profile_probe_t *prof = parg;

	if (prof->prof_kind == PROF_TICK) {
		ASSERT(callout_active(&prof->prof_cyclic));
		callout_stop(&prof->prof_cyclic);
		callout_drain(&prof->prof_cyclic);
	} else {
		ASSERT(prof->prof_kind == PROF_PROFILE);
		profile_disable_omni(prof);
	}
}