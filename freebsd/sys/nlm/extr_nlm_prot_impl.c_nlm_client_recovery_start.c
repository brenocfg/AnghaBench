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
struct nlm_host {int /*<<< orphan*/  nh_monstate; int /*<<< orphan*/  nh_caller_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_MONITORED ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  nlm_client_recovery (struct nlm_host*) ; 
 int /*<<< orphan*/  nlm_host_release (struct nlm_host*) ; 

__attribute__((used)) static void
nlm_client_recovery_start(void *arg)
{
	struct nlm_host *host = (struct nlm_host *) arg;

	NLM_DEBUG(1, "NLM: client lock recovery for %s started\n",
	    host->nh_caller_name);

	nlm_client_recovery(host);

	NLM_DEBUG(1, "NLM: client lock recovery for %s completed\n",
	    host->nh_caller_name);

	host->nh_monstate = NLM_MONITORED;
	nlm_host_release(host);

	kthread_exit();
}