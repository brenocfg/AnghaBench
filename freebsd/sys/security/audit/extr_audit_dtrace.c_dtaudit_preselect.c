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
struct evname_elem {scalar_t__ ene_bsm_probe_enabled; scalar_t__ ene_commit_probe_enabled; } ;
typedef  int /*<<< orphan*/  au_id_t ;
typedef  int /*<<< orphan*/  au_event_t ;
typedef  int /*<<< orphan*/  au_class_t ;

/* Variables and functions */
 struct evname_elem* au_evnamemap_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_dtrace_enabled ; 

__attribute__((used)) static void *
dtaudit_preselect(au_id_t auid, au_event_t event, au_class_t class)
{
	struct evname_elem *ene;
	int probe_enabled;

	/*
	 * NB: Lockless reads here may return a slightly stale value; this is
	 * considered better than acquiring a lock, however.
	 */
	if (!audit_dtrace_enabled)
		return (NULL);
	ene = au_evnamemap_lookup(event);
	if (ene == NULL)
		return (NULL);

	/*
	 * See if either of the two probes for the audit event are enabled.
	 *
	 * NB: Lock also not acquired here -- but perhaps it wouldn't matter
	 * given that we've already used the list lock above?
	 *
	 * XXXRW: Alternatively, au_evnamemap_lookup() could return these
	 * values while holding the list lock...?
	 */
	probe_enabled = ene->ene_commit_probe_enabled ||
	    ene->ene_bsm_probe_enabled;
	if (!probe_enabled)
		return (NULL);
	return ((void *)ene);
}