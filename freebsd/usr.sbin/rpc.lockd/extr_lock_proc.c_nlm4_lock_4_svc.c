#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  stat; } ;
struct TYPE_10__ {TYPE_2__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_3__ nlm4_res ;
struct TYPE_8__ {char* caller_name; char* svid; scalar_t__ l_len; scalar_t__ l_offset; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; } ;
struct TYPE_11__ {char* state; int /*<<< orphan*/  cookie; scalar_t__ reclaim; scalar_t__ exclusive; scalar_t__ block; TYPE_1__ alock; } ;
typedef  TYPE_4__ nlm4_lockargs ;

/* Variables and functions */
 int LOCK_MON ; 
 int LOCK_V4 ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int debug_level ; 
 int /*<<< orphan*/  getlock (TYPE_4__*,struct svc_req*,int) ; 
 int /*<<< orphan*/  log_from_addr (char*,struct svc_req*) ; 
 int /*<<< orphan*/  log_netobj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

nlm4_res *
nlm4_lock_4_svc(nlm4_lockargs *arg, struct svc_req *rqstp)
{
	static nlm4_res res;

	if (debug_level)
		log_from_addr("nlm4_lock", rqstp);
	if (debug_level > 5) {
		syslog(LOG_DEBUG, "Locking arguments:\n");
		log_netobj(&(arg->cookie));
		syslog(LOG_DEBUG, "Alock arguments:\n");
		syslog(LOG_DEBUG, "Caller Name: %s\n",arg->alock.caller_name);
		syslog(LOG_DEBUG, "File Handle:\n");
		log_netobj(&(arg->alock.fh));
		syslog(LOG_DEBUG, "Owner Handle:\n");
		log_netobj(&(arg->alock.oh));
		syslog(LOG_DEBUG, "SVID:        %d\n", arg->alock.svid);
		syslog(LOG_DEBUG, "Lock Offset: %llu\n",
		    (unsigned long long)arg->alock.l_offset);
		syslog(LOG_DEBUG, "Lock Length: %llu\n", 
		    (unsigned long long)arg->alock.l_len);
		syslog(LOG_DEBUG, "Block:       %s\n", (arg->block ? "true" : "false"));
		syslog(LOG_DEBUG, "Exclusive:   %s\n", (arg->exclusive ? "true" : "false"));
		syslog(LOG_DEBUG, "Reclaim:     %s\n", (arg->reclaim ? "true" : "false"));
		syslog(LOG_DEBUG, "State num:   %d\n", arg->state);
	}

	/* copy cookie from arg to result.  See comment in nlm_test_4() */
	res.cookie = arg->cookie;

	res.stat.stat = getlock(arg, rqstp, LOCK_MON | LOCK_V4);
	return (&res);
}