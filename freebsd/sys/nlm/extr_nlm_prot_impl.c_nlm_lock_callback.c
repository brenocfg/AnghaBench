#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rpc_callextra {int /*<<< orphan*/  rc_auth; } ;
struct TYPE_8__ {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  svid; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  caller_name; } ;
struct TYPE_11__ {TYPE_2__ alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  cookie; } ;
struct nlm_async_lock {TYPE_3__* af_host; scalar_t__ af_expiretime; int /*<<< orphan*/  af_rpc; TYPE_6__ af_granted; } ;
struct TYPE_7__ {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  svid; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  caller_name; } ;
struct TYPE_10__ {TYPE_1__ alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_4__ nlm_testargs ;
typedef  int /*<<< orphan*/  ext ;
struct TYPE_9__ {scalar_t__ nh_vers; int /*<<< orphan*/  nh_lock; int /*<<< orphan*/  nh_granted; int /*<<< orphan*/  nh_pending; int /*<<< orphan*/  nh_sysid; int /*<<< orphan*/  nh_caller_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_DEBUG (int,char*,struct nlm_async_lock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NLM_EXPIRE_TIMEOUT ; 
 scalar_t__ NLM_VERS4 ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nlm_async_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nlm_async_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  af_link ; 
 int /*<<< orphan*/  memset (struct rpc_callextra*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_cookie (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_sysid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm4_granted_msg_4 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rpc_callextra*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_auth ; 
 int /*<<< orphan*/  nlm_granted_msg_1 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rpc_callextra*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_zero_tv ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static void
nlm_lock_callback(void *arg, int pending)
{
	struct nlm_async_lock *af = (struct nlm_async_lock *) arg;
	struct rpc_callextra ext;

	NLM_DEBUG(2, "NLM: async lock %p for %s (sysid %d) granted,"
	    " cookie %d:%d\n", af, af->af_host->nh_caller_name,
	    af->af_host->nh_sysid, ng_sysid(&af->af_granted.cookie),
	    ng_cookie(&af->af_granted.cookie));

	/*
	 * Send the results back to the host.
	 *
	 * Note: there is a possible race here with nlm_host_notify
	 * destroying the RPC client. To avoid problems, the first
	 * thing nlm_host_notify does is to cancel pending async lock
	 * requests.
	 */
	memset(&ext, 0, sizeof(ext));
	ext.rc_auth = nlm_auth;
	if (af->af_host->nh_vers == NLM_VERS4) {
		nlm4_granted_msg_4(&af->af_granted,
		    NULL, af->af_rpc, &ext, nlm_zero_tv);
	} else {
		/*
		 * Back-convert to legacy protocol
		 */
		nlm_testargs granted;
		granted.cookie = af->af_granted.cookie;
		granted.exclusive = af->af_granted.exclusive;
		granted.alock.caller_name =
			af->af_granted.alock.caller_name;
		granted.alock.fh = af->af_granted.alock.fh;
		granted.alock.oh = af->af_granted.alock.oh;
		granted.alock.svid = af->af_granted.alock.svid;
		granted.alock.l_offset =
			af->af_granted.alock.l_offset;
		granted.alock.l_len =
			af->af_granted.alock.l_len;

		nlm_granted_msg_1(&granted,
		    NULL, af->af_rpc, &ext, nlm_zero_tv);
	}

	/*
	 * Move this entry to the nh_granted list.
	 */
	af->af_expiretime = time_uptime + NLM_EXPIRE_TIMEOUT;
	mtx_lock(&af->af_host->nh_lock);
	TAILQ_REMOVE(&af->af_host->nh_pending, af, af_link);
	TAILQ_INSERT_TAIL(&af->af_host->nh_granted, af, af_link);
	mtx_unlock(&af->af_host->nh_lock);
}