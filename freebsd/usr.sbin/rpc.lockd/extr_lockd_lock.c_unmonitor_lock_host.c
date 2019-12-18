#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct sm_stat {int dummy; } ;
struct TYPE_2__ {char* my_name; int /*<<< orphan*/  my_proc; int /*<<< orphan*/  my_vers; int /*<<< orphan*/  my_prog; } ;
struct mon_id {char* mon_name; TYPE_1__ my_id; } ;
struct host {int refcnt; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  smon_id ;

/* Variables and functions */
 struct host* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct host* LIST_NEXT (struct host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_PROG ; 
 int /*<<< orphan*/  NLM_SM ; 
 int /*<<< orphan*/  NLM_SM_NOTIFY ; 
 int /*<<< orphan*/  SM_MAXSTRLEN ; 
 int /*<<< orphan*/  SM_PROG ; 
 int /*<<< orphan*/  SM_UNMON ; 
 int /*<<< orphan*/  SM_VERS ; 
 int /*<<< orphan*/  bzero (struct mon_id*,int) ; 
 int callrpc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mon_id*,int /*<<< orphan*/ ,struct sm_stat*) ; 
 int /*<<< orphan*/  debuglog (char*,...) ; 
 int /*<<< orphan*/  free (struct host*) ; 
 int /*<<< orphan*/  hostlst ; 
 int /*<<< orphan*/  hostlst_head ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_mon_id ; 
 scalar_t__ xdr_sm_stat ; 

void
unmonitor_lock_host(char *hostname)
{
	struct host *ihp;
	struct mon_id smon_id;
	struct sm_stat smstat;
	int rpcret;

	rpcret = 0;

	for( ihp=LIST_FIRST(&hostlst_head); ihp != NULL;
	     ihp=LIST_NEXT(ihp, hostlst)) {
		if (strncmp(hostname, ihp->name, SM_MAXSTRLEN) == 0) {
			/* Host is monitored, bump refcount */
			--ihp->refcnt;
			/* Host should only be in the monitor list once */
			break;
		}
	}

	if (ihp == NULL) {
		debuglog("Could not find host %16s in mon list\n", hostname);
		return;
	}

	if (ihp->refcnt > 0)
		return;

	if (ihp->refcnt < 0) {
		debuglog("Negative refcount!: %d\n",
		    ihp->refcnt);
	}

	debuglog("Attempting to unmonitor host %16s\n", hostname);

	bzero(&smon_id,sizeof(smon_id));

	smon_id.mon_name = hostname;
	smon_id.my_id.my_name = "localhost";
	smon_id.my_id.my_prog = NLM_PROG;
	smon_id.my_id.my_vers = NLM_SM;
	smon_id.my_id.my_proc = NLM_SM_NOTIFY;

	rpcret = callrpc("localhost", SM_PROG, SM_VERS, SM_UNMON,
	    (xdrproc_t)xdr_mon_id, &smon_id,
	    (xdrproc_t)xdr_sm_stat, &smstat);

	if (rpcret != 0) {
		debuglog("Rpc call to unmonitor statd failed with "
		   " return value: %d\n", rpcret);
	}

	LIST_REMOVE(ihp, hostlst);
	free(ihp);
}