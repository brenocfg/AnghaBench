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
struct sctp_nat_msg {int msg; } ;
struct sctp_nat_assoc {void* state; } ;
struct libalias {int dummy; } ;

/* Variables and functions */
 void* SN_CL ; 
 int /*<<< orphan*/  SN_C_T (struct libalias*) ; 
 int SN_DROP_PKT ; 
 int SN_NAT_PKT ; 
 void* SN_RM ; 
#define  SN_SCTP_ABORT 130 
#define  SN_SCTP_SHUTACK 129 
#define  SN_SCTP_SHUTCOMP 128 
 int /*<<< orphan*/  SN_X_T (struct libalias*) ; 
 int /*<<< orphan*/  sctp_ResetTimeOut (struct libalias*,struct sctp_nat_assoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_holddown_timer ; 

__attribute__((used)) static int
CL_process(struct libalias *la, int direction,struct sctp_nat_assoc *assoc, struct sctp_nat_msg *sm)
{
	switch (sm->msg) {
	case SN_SCTP_SHUTCOMP:        /* a packet containing a SHUTDOWN-COMPLETE chunk */
		assoc->state = SN_CL;  /* Stay in Close state until timeout */
		if (sysctl_holddown_timer > 0)
			sctp_ResetTimeOut(la, assoc, SN_X_T(la));/* allow to stay open for Tbit packets*/
		else
			assoc->state = SN_RM;/* Mark for removal*/
		return (SN_NAT_PKT);
	case SN_SCTP_SHUTACK:         /* a packet containing a SHUTDOWN-ACK chunk */
		assoc->state = SN_CL;  /* Stay in Close state until timeout */
		sctp_ResetTimeOut(la, assoc, SN_C_T(la));
		return (SN_NAT_PKT);
	case SN_SCTP_ABORT:           /* a packet containing an ABORT chunk */
		assoc->state = SN_RM;/* Mark for removal*/
		return (SN_NAT_PKT);
	default:
		return (SN_DROP_PKT);
	}
	return (SN_DROP_PKT);/* shouldn't get here very bad: log, drop and hope for the best */
}