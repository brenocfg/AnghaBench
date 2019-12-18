#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_11__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ sm_stat ;
struct TYPE_12__ {char* my_name; } ;
typedef  TYPE_4__ my_id ;
typedef  int /*<<< orphan*/  id ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_9__ {int /*<<< orphan*/  my_proc; int /*<<< orphan*/  my_vers; int /*<<< orphan*/  my_prog; int /*<<< orphan*/  my_name; } ;
struct TYPE_10__ {TYPE_1__ my_id; } ;
struct TYPE_13__ {TYPE_2__ mon_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  NLM_PROG ; 
 int /*<<< orphan*/  NLM_SM ; 
 int /*<<< orphan*/  NLM_SM_NOTIFY ; 
 int RPC_PROGUNAVAIL ; 
 int /*<<< orphan*/  SM_PROG ; 
 int /*<<< orphan*/  SM_UNMON_ALL ; 
 int /*<<< orphan*/  SM_VERS ; 
 int callrpc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  clnt_sperrno (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  localhost ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ mon_host ; 
 int /*<<< orphan*/  nsm_state ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_my_id ; 
 scalar_t__ xdr_sm_stat ; 

void
init_nsm(void)
{
	enum clnt_stat ret;
	my_id id;
	sm_stat stat;
	char name[] = "NFS NLM";

	/*
	 * !!!
	 * The my_id structure isn't used by the SM_UNMON_ALL call, as far
	 * as I know.  Leave it empty for now.
	 */
	memset(&id, 0, sizeof(id));
	id.my_name = name;

	/*
	 * !!!
	 * The statd program must already be registered when lockd runs.
	 */
	do {
		ret = callrpc("localhost", SM_PROG, SM_VERS, SM_UNMON_ALL,
		    (xdrproc_t)xdr_my_id, &id, (xdrproc_t)xdr_sm_stat, &stat);
		if (ret == RPC_PROGUNAVAIL) {
			syslog(LOG_WARNING, "%lu %s", SM_PROG,
			    clnt_sperrno(ret));
			sleep(2);
			continue;
		}
		break;
	} while (0);

	if (ret != 0) {
		syslog(LOG_ERR, "%lu %s", SM_PROG, clnt_sperrno(ret));
		exit(1);
	}

	nsm_state = stat.state;

	/* setup constant data for SM_MON calls */
	mon_host.mon_id.my_id.my_name = localhost;
	mon_host.mon_id.my_id.my_prog = NLM_PROG;
	mon_host.mon_id.my_id.my_vers = NLM_SM;
	mon_host.mon_id.my_id.my_proc = NLM_SM_NOTIFY;  /* bsdi addition */
}