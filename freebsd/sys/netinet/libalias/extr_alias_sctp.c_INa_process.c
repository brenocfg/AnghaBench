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
struct sctp_nat_assoc {int TableRegister; void* state; } ;
struct libalias {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IsASCONFack (struct libalias*,struct sctp_nat_msg*,int) ; 
 int SN_BOTH_TBL ; 
 int SN_DROP_PKT ; 
 int /*<<< orphan*/  SN_I_T (struct libalias*) ; 
 int SN_NAT_PKT ; 
 void* SN_RM ; 
#define  SN_SCTP_ABORT 132 
#define  SN_SCTP_ASCONF 131 
#define  SN_SCTP_ASCONFACK 130 
#define  SN_TO_GLOBAL 129 
#define  SN_TO_LOCAL 128 
 void* SN_UP ; 
 int /*<<< orphan*/  SN_U_T (struct libalias*) ; 
 int SN_WAIT_TOGLOBAL ; 
 int SN_WAIT_TOLOCAL ; 
 int /*<<< orphan*/  sctp_ResetTimeOut (struct libalias*,struct sctp_nat_assoc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
INa_process(struct libalias *la, int direction,struct sctp_nat_assoc *assoc, struct sctp_nat_msg *sm)
{
	switch (sm->msg) {
	case SN_SCTP_ASCONF:           /* a packet containing an ASCONF chunk*/
		sctp_ResetTimeOut(la,assoc, SN_I_T(la));
		return (SN_NAT_PKT);
	case SN_SCTP_ASCONFACK:        /* a packet containing an ASCONF chunk with a ADDIP-ACK */
		switch (direction) {
		case SN_TO_LOCAL:
			if (!(assoc->TableRegister & SN_WAIT_TOLOCAL)) /* wrong direction */
				return (SN_DROP_PKT);
			break;
		case SN_TO_GLOBAL:
			if (!(assoc->TableRegister & SN_WAIT_TOGLOBAL)) /* wrong direction */
				return (SN_DROP_PKT);
		}
		if (IsASCONFack(la,sm,direction)) {
			assoc->TableRegister &= SN_BOTH_TBL; /* remove wait flags */
			assoc->state = SN_UP; /* association established for NAT */
			sctp_ResetTimeOut(la,assoc, SN_U_T(la));
			return (SN_NAT_PKT);
		} else {
			assoc->state = SN_RM;/* Mark for removal*/
			return (SN_NAT_PKT);
		}
	case SN_SCTP_ABORT:           /* a packet containing an ABORT chunk */
		assoc->state = SN_RM;/* Mark for removal*/
		return (SN_NAT_PKT);
	default:
		return (SN_DROP_PKT);
	}
	return (SN_DROP_PKT);/* shouldn't get here very bad: log, drop and hope for the best */
}