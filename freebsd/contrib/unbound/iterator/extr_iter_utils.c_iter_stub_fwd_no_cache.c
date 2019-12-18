#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct query_info {int /*<<< orphan*/  qname; int /*<<< orphan*/  qclass; } ;
struct module_qstate {TYPE_1__* env; } ;
struct iter_hints_stub {TYPE_2__* dp; } ;
struct delegpt {int no_cache; int /*<<< orphan*/  name; int /*<<< orphan*/  namelabs; } ;
struct TYPE_4__ {int no_cache; int /*<<< orphan*/  name; int /*<<< orphan*/  namelabs; } ;
struct TYPE_3__ {int /*<<< orphan*/  fwds; int /*<<< orphan*/  hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dname_strict_subdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct delegpt* forwards_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iter_hints_stub* hints_lookup_stub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char*,char*) ; 

int
iter_stub_fwd_no_cache(struct module_qstate *qstate, struct query_info *qinf)
{
	struct iter_hints_stub *stub;
	struct delegpt *dp;

	/* Check for stub. */
	stub = hints_lookup_stub(qstate->env->hints, qinf->qname,
	    qinf->qclass, NULL);
	dp = forwards_lookup(qstate->env->fwds, qinf->qname, qinf->qclass);

	/* see if forward or stub is more pertinent */
	if(stub && stub->dp && dp) {
		if(dname_strict_subdomain(dp->name, dp->namelabs,
			stub->dp->name, stub->dp->namelabs)) {
			stub = NULL; /* ignore stub, forward is lower */
		} else {
			dp = NULL; /* ignore forward, stub is lower */
		}
	}

	/* check stub */
	if (stub != NULL && stub->dp != NULL) {
		if(stub->dp->no_cache) {
			char qname[255+1];
			char dpname[255+1];
			dname_str(qinf->qname, qname);
			dname_str(stub->dp->name, dpname);
			verbose(VERB_ALGO, "stub for %s %s has no_cache", qname, dpname);
		}
		return (stub->dp->no_cache);
	}

	/* Check for forward. */
	if (dp) {
		if(dp->no_cache) {
			char qname[255+1];
			char dpname[255+1];
			dname_str(qinf->qname, qname);
			dname_str(dp->name, dpname);
			verbose(VERB_ALGO, "forward for %s %s has no_cache", qname, dpname);
		}
		return (dp->no_cache);
	}
	return 0;
}