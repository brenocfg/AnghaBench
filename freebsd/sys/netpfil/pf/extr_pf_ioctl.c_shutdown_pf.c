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
typedef  int /*<<< orphan*/  u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPFPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PF_DEBUG_MISC ; 
 int /*<<< orphan*/  PF_RULESET_BINAT ; 
 int /*<<< orphan*/  PF_RULESET_FILTER ; 
 int /*<<< orphan*/  PF_RULESET_NAT ; 
 int /*<<< orphan*/  PF_RULESET_RDR ; 
 int /*<<< orphan*/  PF_RULESET_SCRUB ; 
 int pf_begin_altq (int /*<<< orphan*/ *) ; 
 int pf_begin_rules (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pf_clear_srcnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_clear_states () ; 
 int pf_clear_tables () ; 
 int /*<<< orphan*/  pf_commit_altq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_commit_rules (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
shutdown_pf(void)
{
	int error = 0;
	u_int32_t t[5];
	char nn = '\0';

	do {
		if ((error = pf_begin_rules(&t[0], PF_RULESET_SCRUB, &nn))
		    != 0) {
			DPFPRINTF(PF_DEBUG_MISC, ("shutdown_pf: SCRUB\n"));
			break;
		}
		if ((error = pf_begin_rules(&t[1], PF_RULESET_FILTER, &nn))
		    != 0) {
			DPFPRINTF(PF_DEBUG_MISC, ("shutdown_pf: FILTER\n"));
			break;		/* XXX: rollback? */
		}
		if ((error = pf_begin_rules(&t[2], PF_RULESET_NAT, &nn))
		    != 0) {
			DPFPRINTF(PF_DEBUG_MISC, ("shutdown_pf: NAT\n"));
			break;		/* XXX: rollback? */
		}
		if ((error = pf_begin_rules(&t[3], PF_RULESET_BINAT, &nn))
		    != 0) {
			DPFPRINTF(PF_DEBUG_MISC, ("shutdown_pf: BINAT\n"));
			break;		/* XXX: rollback? */
		}
		if ((error = pf_begin_rules(&t[4], PF_RULESET_RDR, &nn))
		    != 0) {
			DPFPRINTF(PF_DEBUG_MISC, ("shutdown_pf: RDR\n"));
			break;		/* XXX: rollback? */
		}

		/* XXX: these should always succeed here */
		pf_commit_rules(t[0], PF_RULESET_SCRUB, &nn);
		pf_commit_rules(t[1], PF_RULESET_FILTER, &nn);
		pf_commit_rules(t[2], PF_RULESET_NAT, &nn);
		pf_commit_rules(t[3], PF_RULESET_BINAT, &nn);
		pf_commit_rules(t[4], PF_RULESET_RDR, &nn);

		if ((error = pf_clear_tables()) != 0)
			break;

#ifdef ALTQ
		if ((error = pf_begin_altq(&t[0])) != 0) {
			DPFPRINTF(PF_DEBUG_MISC, ("shutdown_pf: ALTQ\n"));
			break;
		}
		pf_commit_altq(t[0]);
#endif

		pf_clear_states();

		pf_clear_srcnodes(NULL);

		/* status does not use malloced mem so no need to cleanup */
		/* fingerprints and interfaces have their own cleanup code */
	} while(0);

	return (error);
}