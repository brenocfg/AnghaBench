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

/* Variables and functions */
#define  SN_SCTP_ABORT 137 
#define  SN_SCTP_ASCONF 136 
#define  SN_SCTP_ASCONFACK 135 
#define  SN_SCTP_INIT 134 
#define  SN_SCTP_INITACK 133 
#define  SN_SCTP_OTHER 132 
#define  SN_SCTP_SHUTACK 131 
#define  SN_SCTP_SHUTCOMP 130 
#define  SN_TO_GLOBAL 129 
#define  SN_TO_LOCAL 128 
 int /*<<< orphan*/  SctpAliasLog (char*,char*,char*) ; 

__attribute__((used)) static void
logsctpparse(int direction, struct sctp_nat_msg *sm)
{
	char *ploc, *pstate;
	switch (direction) {
	case SN_TO_LOCAL:
		ploc = "TO_LOCAL -";
		break;
	case SN_TO_GLOBAL:
		ploc = "TO_GLOBAL -";
		break;
	default:
		ploc = "";
	}
	switch (sm->msg) {
	case SN_SCTP_INIT:
		pstate = "Init";
		break;
	case SN_SCTP_INITACK:
		pstate = "InitAck";
		break;
	case SN_SCTP_ABORT:
		pstate = "Abort";
		break;
	case SN_SCTP_SHUTACK:
		pstate = "ShutAck";
		break;
	case SN_SCTP_SHUTCOMP:
		pstate = "ShutComp";
		break;
	case SN_SCTP_ASCONF:
		pstate = "Asconf";
		break;
	case SN_SCTP_ASCONFACK:
		pstate = "AsconfAck";
		break;
	case SN_SCTP_OTHER:
		pstate = "Other";
		break;
	default:
		pstate = "***ERROR***";
		break;
	}
	SctpAliasLog("Parsed: %s %s\n", ploc, pstate);
}