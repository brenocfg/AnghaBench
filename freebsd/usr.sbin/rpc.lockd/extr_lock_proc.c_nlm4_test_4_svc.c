#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct nlm4_holder {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  holder; } ;
struct TYPE_9__ {TYPE_1__ nlm4_testrply_u; int /*<<< orphan*/  stat; } ;
struct TYPE_10__ {TYPE_2__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_3__ nlm4_testres ;
struct TYPE_12__ {char* caller_name; char* svid; scalar_t__ l_len; scalar_t__ l_offset; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; } ;
struct TYPE_11__ {int /*<<< orphan*/  cookie; scalar_t__ exclusive; TYPE_5__ alock; } ;
typedef  TYPE_4__ nlm4_testargs ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_V4 ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int debug_level ; 
 int /*<<< orphan*/  log_from_addr (char*,struct svc_req*) ; 
 int /*<<< orphan*/  log_netobj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct nlm4_holder*,int) ; 
 int /*<<< orphan*/  nlm4_denied ; 
 int /*<<< orphan*/  nlm4_granted ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 struct nlm4_holder* testlock (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 

nlm4_testres *
nlm4_test_4_svc(nlm4_testargs *arg, struct svc_req *rqstp)
{
	static nlm4_testres res;
	struct nlm4_holder *holder;

	if (debug_level)
		log_from_addr("nlm4_test", rqstp);
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
		syslog(LOG_DEBUG, "Exclusive:   %s\n",
		    (arg->exclusive ? "true" : "false"));
	}

	holder = testlock(&arg->alock, arg->exclusive, LOCK_V4);

	/*
	 * Copy the cookie from the argument into the result.  Note that this
	 * is slightly hazardous, as the structure contains a pointer to a
	 * malloc()ed buffer that will get freed by the caller.  However, the
	 * main function transmits the result before freeing the argument
	 * so it is in fact safe.
	 */
	res.cookie = arg->cookie;
	if (holder == NULL) {
		res.stat.stat = nlm4_granted;
	} else {
		res.stat.stat = nlm4_denied;
		memcpy(&res.stat.nlm4_testrply_u.holder, holder,
		    sizeof(struct nlm4_holder));
	}
	return (&res);
}