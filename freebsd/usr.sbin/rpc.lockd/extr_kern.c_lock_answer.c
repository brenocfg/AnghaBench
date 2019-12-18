#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_5__ {int pid; int msg_seq; } ;
struct lockd_ans {int la_set_getlk_pid; int la_getlk_pid; TYPE_2__ la_msg_ident; void* la_errno; } ;
struct TYPE_4__ {int n_len; int /*<<< orphan*/  n_bytes; } ;
typedef  TYPE_1__ netobj ;

/* Variables and functions */
 void* EACCES ; 
 void* EAGAIN ; 
 void* EDEADLK ; 
 void* EFBIG ; 
 scalar_t__ EPIPE ; 
 void* EROFS ; 
 scalar_t__ ESRCH ; 
 void* ESTALE ; 
 int /*<<< orphan*/  LOCKD_ANS_VERSION ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int NLM_VERS4 ; 
 scalar_t__ d_calls ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nfslockdans (int /*<<< orphan*/ ,struct lockd_ans*) ; 
#define  nlm4_blocked 143 
#define  nlm4_deadlck 142 
#define  nlm4_denied 141 
#define  nlm4_denied_grace_period 140 
#define  nlm4_denied_nolocks 139 
#define  nlm4_failed 138 
#define  nlm4_fbig 137 
#define  nlm4_granted 136 
#define  nlm4_rofs 135 
#define  nlm4_stale_fh 134 
#define  nlm_blocked 133 
#define  nlm_deadlck 132 
#define  nlm_denied 131 
#define  nlm_denied_grace_period 130 
#define  nlm_denied_nolocks 129 
#define  nlm_granted 128 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

int
lock_answer(int pid, netobj *netcookie, int result, int *pid_p, int version)
{
	struct lockd_ans ans;

	if (netcookie->n_len != sizeof(ans.la_msg_ident)) {
		if (pid == -1) {	/* we're screwed */
			syslog(LOG_ERR, "inedible nlm cookie");
			return -1;
		}
		ans.la_msg_ident.pid = pid;
		ans.la_msg_ident.msg_seq = -1;
	} else {
		memcpy(&ans.la_msg_ident, netcookie->n_bytes,
		    sizeof(ans.la_msg_ident));
	}

	if (d_calls)
		syslog(LOG_DEBUG, "lock answer: pid %lu: %s %d",
		    (unsigned long)ans.la_msg_ident.pid,
		    version == NLM_VERS4 ? "nlmv4" : "nlmv3",
		    result);

	ans.la_set_getlk_pid = 0;
	if (version == NLM_VERS4)
		switch (result) {
		case nlm4_granted:
			ans.la_errno = 0;
			break;
		default:
			ans.la_errno = EACCES;
			break;
		case nlm4_denied:
			if (pid_p == NULL)
				ans.la_errno = EAGAIN;
			else {
				/* this is an answer to a nlm_test msg */
				ans.la_set_getlk_pid = 1;
				ans.la_getlk_pid = *pid_p;
				ans.la_errno = 0;
			}
			break;
		case nlm4_denied_nolocks:
			ans.la_errno = EAGAIN;
			break;
		case nlm4_blocked:
			return -1;
			/* NOTREACHED */
		case nlm4_denied_grace_period:
			ans.la_errno = EAGAIN;
			break;
		case nlm4_deadlck:
			ans.la_errno = EDEADLK;
			break;
		case nlm4_rofs:
			ans.la_errno = EROFS;
			break;
		case nlm4_stale_fh:
			ans.la_errno = ESTALE;
			break;
		case nlm4_fbig:
			ans.la_errno = EFBIG;
			break;
		case nlm4_failed:
			ans.la_errno = EACCES;
			break;
		}
	else
		switch (result) {
		case nlm_granted:
			ans.la_errno = 0;
			break;
		default:
			ans.la_errno = EACCES;
			break;
		case nlm_denied:
			if (pid_p == NULL)
				ans.la_errno = EAGAIN;
			else {
				/* this is an answer to a nlm_test msg */
				ans.la_set_getlk_pid = 1;
				ans.la_getlk_pid = *pid_p;
				ans.la_errno = 0;
			}
			break;
		case nlm_denied_nolocks:
			ans.la_errno = EAGAIN;
			break;
		case nlm_blocked:
			return -1;
			/* NOTREACHED */
		case nlm_denied_grace_period:
			ans.la_errno = EAGAIN;
			break;
		case nlm_deadlck:
			ans.la_errno = EDEADLK;
			break;
		}

	if (nfslockdans(LOCKD_ANS_VERSION, &ans)) {
		syslog(((errno == EPIPE || errno == ESRCH) ? 
			LOG_INFO : LOG_ERR), 
			"process %lu: %m", (u_long)ans.la_msg_ident.pid);
		return -1;
	}
	return 0;
}