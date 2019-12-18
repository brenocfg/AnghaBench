#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct nlm_host {int nh_state; int nh_caller_name; scalar_t__ nh_monstate; int /*<<< orphan*/  nh_lock; int /*<<< orphan*/  nh_sysid; } ;
struct TYPE_9__ {scalar_t__ res_stat; } ;
typedef  TYPE_3__ sm_stat_res ;
struct TYPE_7__ {char* my_name; int /*<<< orphan*/  my_proc; int /*<<< orphan*/  my_vers; int /*<<< orphan*/  my_prog; } ;
struct TYPE_8__ {int mon_name; TYPE_1__ my_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  priv; TYPE_2__ mon_id; } ;
typedef  TYPE_4__ mon ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;

/* Variables and functions */
 int CLNT_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,struct timeval) ; 
 int /*<<< orphan*/  NLM_DEBUG (int,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  NLM_ERR (char*,int) ; 
 void* NLM_MONITORED ; 
 scalar_t__ NLM_MONITOR_FAILED ; 
 int /*<<< orphan*/  NLM_PROG ; 
 int /*<<< orphan*/  NLM_SM ; 
 int /*<<< orphan*/  NLM_SM_NOTIFY ; 
 scalar_t__ NLM_UNMONITORED ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  SM_MON ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_nsm ; 
 scalar_t__ stat_fail ; 
 scalar_t__ xdr_mon ; 
 scalar_t__ xdr_sm_stat ; 

void
nlm_host_monitor(struct nlm_host *host, int state)
{
	mon smmon;
	sm_stat_res smstat;
	struct timeval timo;
	enum clnt_stat stat;

	if (state && !host->nh_state) {
		/*
		 * This is the first time we have seen an NSM state
		 * value for this host. We record it here to help
		 * detect host reboots.
		 */
		host->nh_state = state;
		NLM_DEBUG(1, "NLM: host %s (sysid %d) has NSM state %d\n",
		    host->nh_caller_name, host->nh_sysid, state);
	}

	mtx_lock(&host->nh_lock);
	if (host->nh_monstate != NLM_UNMONITORED) {
		mtx_unlock(&host->nh_lock);
		return;
	}
	host->nh_monstate = NLM_MONITORED;
	mtx_unlock(&host->nh_lock);

	NLM_DEBUG(1, "NLM: monitoring %s (sysid %d)\n",
	    host->nh_caller_name, host->nh_sysid);

	/*
	 * We put our assigned system ID value in the priv field to
	 * make it simpler to find the host if we are notified of a
	 * host restart.
	 */
	smmon.mon_id.mon_name = host->nh_caller_name;
	smmon.mon_id.my_id.my_name = "localhost";
	smmon.mon_id.my_id.my_prog = NLM_PROG;
	smmon.mon_id.my_id.my_vers = NLM_SM;
	smmon.mon_id.my_id.my_proc = NLM_SM_NOTIFY;
	memcpy(smmon.priv, &host->nh_sysid, sizeof(host->nh_sysid));

	timo.tv_sec = 25;
	timo.tv_usec = 0;
	stat = CLNT_CALL(nlm_nsm, SM_MON,
	    (xdrproc_t) xdr_mon, &smmon,
	    (xdrproc_t) xdr_sm_stat, &smstat, timo);

	if (stat != RPC_SUCCESS) {
		NLM_ERR("Failed to contact local NSM - rpc error %d\n", stat);
		return;
	}
	if (smstat.res_stat == stat_fail) {
		NLM_ERR("Local NSM refuses to monitor %s\n",
		    host->nh_caller_name);
		mtx_lock(&host->nh_lock);
		host->nh_monstate = NLM_MONITOR_FAILED;
		mtx_unlock(&host->nh_lock);
		return;
	}

	host->nh_monstate = NLM_MONITORED;
}