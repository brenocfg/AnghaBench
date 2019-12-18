#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ prof_kind; scalar_t__ prof_expected; int /*<<< orphan*/  prof_cyclic; scalar_t__ prof_interval; } ;
typedef  TYPE_1__ profile_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int C_ABSOLUTE ; 
 int C_DIRECT_EXEC ; 
 scalar_t__ PROF_PROFILE ; 
 scalar_t__ PROF_TICK ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  profile_enable_omni (TYPE_1__*) ; 
 int /*<<< orphan*/  profile_tick ; 
 scalar_t__ sbinuptime () ; 

__attribute__((used)) static void
profile_enable(void *arg, dtrace_id_t id, void *parg)
{
	profile_probe_t *prof = parg;

	if (prof->prof_kind == PROF_TICK) {
		prof->prof_expected = sbinuptime() + prof->prof_interval;
		callout_reset_sbt(&prof->prof_cyclic,
		    prof->prof_expected, 0, profile_tick, prof,
		    C_DIRECT_EXEC | C_ABSOLUTE);
	} else {
		ASSERT(prof->prof_kind == PROF_PROFILE);
		profile_enable_omni(prof);
	}
}