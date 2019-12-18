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
struct tcpcb {int /*<<< orphan*/  t_inpcb; struct tcp_log_id_bucket* t_lib; } ;
struct tcp_log_id_bucket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TCPID_BUCKET_LOCK (struct tcp_log_id_bucket*) ; 
 int /*<<< orphan*/  TCPID_BUCKET_REF (struct tcp_log_id_bucket*) ; 
 int /*<<< orphan*/  TCPID_TREE_RUNLOCK () ; 
 int /*<<< orphan*/  TCPID_TREE_WUNLOCK () ; 
#define  TREE_RLOCKED 129 
 int TREE_UNLOCKED ; 
#define  TREE_WLOCKED 128 
 int /*<<< orphan*/  tcp_log_dump_tp_logbuf (struct tcpcb*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_log_dumpbucketlogs (struct tcp_log_id_bucket*,char*) ; 
 scalar_t__ tcp_log_unref_bucket (struct tcp_log_id_bucket*,int*,int /*<<< orphan*/ *) ; 

void
tcp_log_dump_tp_bucket_logbufs(struct tcpcb *tp, char *reason)
{
	struct tcp_log_id_bucket *tlb;
	int tree_locked;

	/* Figure out our bucket and lock it. */
	INP_WLOCK_ASSERT(tp->t_inpcb);
	tlb = tp->t_lib;
	if (tlb == NULL) {
		/*
		 * No bucket; treat this like a request to dump a single
		 * session's traces.
		 */
		(void)tcp_log_dump_tp_logbuf(tp, reason, M_WAITOK, true);
		INP_WUNLOCK(tp->t_inpcb);
		return;
	}
	TCPID_BUCKET_REF(tlb);
	INP_WUNLOCK(tp->t_inpcb);
	TCPID_BUCKET_LOCK(tlb);

	/* If we are the last reference, we have nothing more to do here. */
	tree_locked = TREE_UNLOCKED;
	if (tcp_log_unref_bucket(tlb, &tree_locked, NULL)) {
		switch (tree_locked) {
		case TREE_WLOCKED:
			TCPID_TREE_WUNLOCK();
			break;
		case TREE_RLOCKED:
			TCPID_TREE_RUNLOCK();
			break;
		}
		return;
	}

	/* Turn this over to tcp_log_dumpbucketlogs() to finish the work. */ 
	tcp_log_dumpbucketlogs(tlb, reason);
}