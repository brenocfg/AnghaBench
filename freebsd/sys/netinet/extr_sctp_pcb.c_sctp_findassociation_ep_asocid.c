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
struct sctp_tcb {int dummy; } ;
struct sctp_inpcb {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_assoc_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_INP_RLOCK (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_RUNLOCK (struct sctp_inpcb*) ; 
 struct sctp_tcb* sctp_findasoc_ep_asocid_locked (struct sctp_inpcb*,int /*<<< orphan*/ ,int) ; 

struct sctp_tcb *
sctp_findassociation_ep_asocid(struct sctp_inpcb *inp, sctp_assoc_t asoc_id, int want_lock)
{
	struct sctp_tcb *stcb;

	SCTP_INP_RLOCK(inp);
	stcb = sctp_findasoc_ep_asocid_locked(inp, asoc_id, want_lock);
	SCTP_INP_RUNLOCK(inp);
	return (stcb);
}