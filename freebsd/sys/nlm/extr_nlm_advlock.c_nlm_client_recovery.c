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
struct nlm_recovery_context {int /*<<< orphan*/  nr_state; struct nlm_host* nr_host; } ;
struct nlm_host {int dummy; } ;

/* Variables and functions */
 int ERESTART ; 
 int NLM_SYSID_CLIENT ; 
 int lf_iteratelocks_sysid (int,int /*<<< orphan*/ ,struct nlm_recovery_context*) ; 
 int /*<<< orphan*/  nlm_client_recover_lock ; 
 int /*<<< orphan*/  nlm_host_get_state (struct nlm_host*) ; 
 int nlm_host_get_sysid (struct nlm_host*) ; 

void
nlm_client_recovery(struct nlm_host *host)
{
	struct nlm_recovery_context nr;
	int sysid, error;

	sysid = NLM_SYSID_CLIENT | nlm_host_get_sysid(host);
	do {
		nr.nr_host = host;
		nr.nr_state = nlm_host_get_state(host);
		error = lf_iteratelocks_sysid(sysid,
		    nlm_client_recover_lock, &nr);
	} while (error == ERESTART);
}