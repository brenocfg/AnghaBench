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
struct evname_elem {scalar_t__ ene_commit_probe_id; scalar_t__ ene_bsm_probe_id; int /*<<< orphan*/ * ene_name; } ;
typedef  int /*<<< orphan*/  ene_name_lower ;

/* Variables and functions */
 int EVNAMEMAP_NAME_SIZE ; 
 int /*<<< orphan*/  dtaudit_id ; 
 int /*<<< orphan*/  dtaudit_module_str ; 
 int /*<<< orphan*/  dtaudit_name_bsm_str ; 
 int /*<<< orphan*/  dtaudit_name_commit_str ; 
 void* dtrace_probe_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct evname_elem*) ; 
 scalar_t__ dtrace_probe_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtaudit_au_evnamemap_callback(struct evname_elem *ene)
{
	char ene_name_lower[EVNAMEMAP_NAME_SIZE];
	int i;

	/*
	 * DTrace, by convention, has lower-case probe names.  However, the
	 * in-kernel event-to-name mapping table must maintain event-name case
	 * as submitted by userspace.  Create a temporary lower-case version
	 * here, away from the fast path, to use when exposing the event name
	 * to DTrace as part of the name of a probe.
	 *
	 * NB: Convert the entire array, including the terminating nul,
	 * because these strings are short and it's more work not to.  If they
	 * become long, we might feel more guilty about this sloppiness!
	 */
	for (i = 0; i < sizeof(ene_name_lower); i++)
		ene_name_lower[i] = tolower(ene->ene_name[i]);

	/*
	 * Don't register a new probe if this event number already has an
	 * associated commit probe -- or if another event has already
	 * registered this name.
	 *
	 * XXXRW: There is an argument that if multiple numeric events match
	 * a single name, they should all be exposed to the same named probe.
	 * In particular, we should perhaps use a probe ID returned by this
	 * lookup and just stick that in the saved probe ID?
	 */
	if ((ene->ene_commit_probe_id == 0) &&
	    (dtrace_probe_lookup(dtaudit_id, dtaudit_module_str,
	    ene_name_lower, dtaudit_name_commit_str) == 0)) {

		/*
		 * Create the commit probe.
		 *
		 * NB: We don't declare any extra stack frames because stack()
		 * will just return the path to the audit commit code, which
		 * is not really interesting anyway.
		 *
		 * We pass in the pointer to the evnam_elem entry so that we
		 * can easily change its enabled flag in the probe
		 * enable/disable interface.
		 */
		ene->ene_commit_probe_id = dtrace_probe_create(dtaudit_id,
		    dtaudit_module_str, ene_name_lower,
		    dtaudit_name_commit_str, 0, ene);
	}

	/*
	 * Don't register a new probe if this event number already has an
	 * associated bsm probe -- or if another event has already
	 * registered this name.
	 *
	 * XXXRW: There is an argument that if multiple numeric events match
	 * a single name, they should all be exposed to the same named probe.
	 * In particular, we should perhaps use a probe ID returned by this
	 * lookup and just stick that in the saved probe ID?
	 */
	if ((ene->ene_bsm_probe_id == 0) &&
	    (dtrace_probe_lookup(dtaudit_id, dtaudit_module_str,
	    ene_name_lower, dtaudit_name_bsm_str) == 0)) {

		/*
		 * Create the bsm probe.
		 *
		 * NB: We don't declare any extra stack frames because stack()
		 * will just return the path to the audit commit code, which
		 * is not really interesting anyway.
		 *
		 * We pass in the pointer to the evnam_elem entry so that we
		 * can easily change its enabled flag in the probe
		 * enable/disable interface.
		 */
		ene->ene_bsm_probe_id = dtrace_probe_create(dtaudit_id,
		    dtaudit_module_str, ene_name_lower, dtaudit_name_bsm_str,
		    0, ene);
	}
}