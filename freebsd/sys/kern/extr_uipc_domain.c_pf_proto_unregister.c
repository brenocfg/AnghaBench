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
struct protosw {int pr_type; int pr_protocol; int /*<<< orphan*/ * pr_usrreqs; int /*<<< orphan*/ * pr_drain; int /*<<< orphan*/ * pr_slowtimo; int /*<<< orphan*/ * pr_fasttimo; int /*<<< orphan*/ * pr_init; int /*<<< orphan*/ * pr_ctloutput; int /*<<< orphan*/ * pr_ctlinput; int /*<<< orphan*/ * pr_output; int /*<<< orphan*/ * pr_input; scalar_t__ pr_flags; struct domain* pr_domain; } ;
struct domain {struct protosw* dom_protoswNPROTOSW; struct protosw* dom_protosw; } ;

/* Variables and functions */
 int EMLINK ; 
 int EPFNOSUPPORT ; 
 int EPROTONOSUPPORT ; 
 int EPROTOTYPE ; 
 int PROTO_SPACER ; 
 int /*<<< orphan*/  dom_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nousrreqs ; 
 struct domain* pffinddomain (int) ; 

int
pf_proto_unregister(int family, int protocol, int type)
{
	struct domain *dp;
	struct protosw *pr, *dpr;

	/* Sanity checks. */
	if (family == 0)
		return (EPFNOSUPPORT);
	if (protocol == 0)
		return (EPROTONOSUPPORT);
	if (type == 0)
		return (EPROTOTYPE);

	/* Try to find the specified domain based on the family type. */
	dp = pffinddomain(family);
	if (dp == NULL)
		return (EPFNOSUPPORT);

	dpr = NULL;

	/* Lock out everyone else while we are manipulating the protosw. */
	mtx_lock(&dom_mtx);

	/* The protocol must exist and only once. */
	for (pr = dp->dom_protosw; pr < dp->dom_protoswNPROTOSW; pr++) {
		if ((pr->pr_type == type) && (pr->pr_protocol == protocol)) {
			if (dpr != NULL) {
				mtx_unlock(&dom_mtx);
				return (EMLINK);   /* Should not happen! */
			} else
				dpr = pr;
		}
	}

	/* Protocol does not exist. */
	if (dpr == NULL) {
		mtx_unlock(&dom_mtx);
		return (EPROTONOSUPPORT);
	}

	/* De-orbit the protocol and make the slot available again. */
	dpr->pr_type = 0;
	dpr->pr_domain = dp;
	dpr->pr_protocol = PROTO_SPACER;
	dpr->pr_flags = 0;
	dpr->pr_input = NULL;
	dpr->pr_output = NULL;
	dpr->pr_ctlinput = NULL;
	dpr->pr_ctloutput = NULL;
	dpr->pr_init = NULL;
	dpr->pr_fasttimo = NULL;
	dpr->pr_slowtimo = NULL;
	dpr->pr_drain = NULL;
	dpr->pr_usrreqs = &nousrreqs;

	/* Job is done, not more protection required. */
	mtx_unlock(&dom_mtx);

	return (0);
}