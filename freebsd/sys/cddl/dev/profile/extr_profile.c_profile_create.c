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
struct TYPE_4__ {int prof_kind; int /*<<< orphan*/  prof_id; int /*<<< orphan*/  prof_cyclic; scalar_t__ prof_interval; int /*<<< orphan*/  prof_name; } ;
typedef  TYPE_1__ profile_probe_t ;
typedef  scalar_t__ hrtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CYCLIC_NONE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  atomic_add_32 (scalar_t__*,int) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dtrace_probe_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ dtrace_probe_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nsec_to_sbt (scalar_t__) ; 
 int /*<<< orphan*/  profile_aframes ; 
 int /*<<< orphan*/  profile_id ; 
 scalar_t__ profile_interval_min ; 
 scalar_t__ profile_max ; 
 scalar_t__ profile_total ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
profile_create(hrtime_t interval, char *name, int kind)
{
	profile_probe_t *prof;

	if (interval < profile_interval_min)
		return;

	if (dtrace_probe_lookup(profile_id, NULL, NULL, name) != 0)
		return;

	atomic_add_32(&profile_total, 1);
	if (profile_total > profile_max) {
		atomic_add_32(&profile_total, -1);
		return;
	}

	prof = kmem_zalloc(sizeof (profile_probe_t), KM_SLEEP);
	(void) strcpy(prof->prof_name, name);
#ifdef illumos
	prof->prof_interval = interval;
	prof->prof_cyclic = CYCLIC_NONE;
#else
	prof->prof_interval = nsec_to_sbt(interval);
	callout_init(&prof->prof_cyclic, 1);
#endif
	prof->prof_kind = kind;
	prof->prof_id = dtrace_probe_create(profile_id,
	    NULL, NULL, name,
	    profile_aframes, prof);
}