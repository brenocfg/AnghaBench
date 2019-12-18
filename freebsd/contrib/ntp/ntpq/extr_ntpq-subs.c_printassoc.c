#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int status; int assid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CTL_PEER_EVENT (int) ; 
 int /*<<< orphan*/  CTL_PEER_NEVNT (int) ; 
 scalar_t__ CTL_PEER_STATVAL (int) ; 
 int CTL_PST_AUTHENABLE ; 
 int CTL_PST_AUTHENTIC ; 
 int CTL_PST_BCAST ; 
 int CTL_PST_CONFIG ; 
 int CTL_PST_REACH ; 
#define  CTL_PST_SEL_CORRECT 150 
#define  CTL_PST_SEL_EXCESS 149 
#define  CTL_PST_SEL_PPS 148 
#define  CTL_PST_SEL_REJECT 147 
#define  CTL_PST_SEL_SANE 146 
#define  CTL_PST_SEL_SELCAND 145 
#define  CTL_PST_SEL_SYNCCAND 144 
#define  CTL_PST_SEL_SYSPEER 143 
 scalar_t__ NTP_OLDVERSION ; 
 int OLD_CTL_PST_DISP ; 
 int OLD_CTL_PST_SANE ; 
#define  OLD_CTL_PST_SEL_REJECT 142 
#define  OLD_CTL_PST_SEL_SELCAND 141 
#define  OLD_CTL_PST_SEL_SYNCCAND 140 
#define  OLD_CTL_PST_SEL_SYSPEER 139 
 int PEER_EVENT ; 
#define  PEVNT_ARMED 138 
#define  PEVNT_CLOCK 137 
#define  PEVNT_DEMOBIL 136 
#define  PEVNT_DENY 135 
#define  PEVNT_MOBIL 134 
#define  PEVNT_NEWPEER 133 
#define  PEVNT_RATE 132 
#define  PEVNT_REACH 131 
#define  PEVNT_REPLY 130 
#define  PEVNT_RESTART 129 
#define  PEVNT_UNREACH 128 
 TYPE_1__* assoc_cache ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ numassoc ; 
 scalar_t__ pktversion ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__,int,int,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
printassoc(
	int showall,
	FILE *fp
	)
{
	register char *bp;
	u_int i;
	u_char statval;
	int event;
	u_long event_count;
	const char *conf;
	const char *reach;
	const char *auth;
	const char *condition = "";
	const char *last_event;
	char buf[128];

	if (numassoc == 0) {
		(void) fprintf(fp, "No association ID's in list\n");
		return;
	}

	/*
	 * Output a header
	 */
	(void) fprintf(fp,
			   "ind assid status  conf reach auth condition  last_event cnt\n");
	(void) fprintf(fp,
			   "===========================================================\n");
	for (i = 0; i < numassoc; i++) {
		statval = (u_char) CTL_PEER_STATVAL(assoc_cache[i].status);
		if (!showall && !(statval & (CTL_PST_CONFIG|CTL_PST_REACH)))
			continue;
		event = CTL_PEER_EVENT(assoc_cache[i].status);
		event_count = CTL_PEER_NEVNT(assoc_cache[i].status);
		if (statval & CTL_PST_CONFIG)
			conf = "yes";
		else
			conf = "no";
		if (statval & CTL_PST_BCAST) {
			reach = "none";
			if (statval & CTL_PST_AUTHENABLE)
				auth = "yes";
			else
				auth = "none";
		} else {
			if (statval & CTL_PST_REACH)
				reach = "yes";
			else
				reach = "no";
			if (statval & CTL_PST_AUTHENABLE) {
				if (statval & CTL_PST_AUTHENTIC)
					auth = "ok ";
				else
					auth = "bad";
			} else {
				auth = "none";
			}
		}
		if (pktversion > NTP_OLDVERSION) {
			switch (statval & 0x7) {

			case CTL_PST_SEL_REJECT:
				condition = "reject";
				break;

			case CTL_PST_SEL_SANE:
				condition = "falsetick";
				break;

			case CTL_PST_SEL_CORRECT:
				condition = "excess";
				break;

			case CTL_PST_SEL_SELCAND:
				condition = "outlier";
				break;

			case CTL_PST_SEL_SYNCCAND:
				condition = "candidate";
				break;

			case CTL_PST_SEL_EXCESS:
				condition = "backup";
				break;

			case CTL_PST_SEL_SYSPEER:
				condition = "sys.peer";
				break;

			case CTL_PST_SEL_PPS:
				condition = "pps.peer";
				break;
			}
		} else {
			switch (statval & 0x3) {

			case OLD_CTL_PST_SEL_REJECT:
				if (!(statval & OLD_CTL_PST_SANE))
					condition = "insane";
				else if (!(statval & OLD_CTL_PST_DISP))
					condition = "hi_disp";
				else
					condition = "";
				break;

			case OLD_CTL_PST_SEL_SELCAND:
				condition = "sel_cand";
				break;

			case OLD_CTL_PST_SEL_SYNCCAND:
				condition = "sync_cand";
				break;

			case OLD_CTL_PST_SEL_SYSPEER:
				condition = "sys_peer";
				break;
			}
		}
		switch (PEER_EVENT|event) {

		case PEVNT_MOBIL:
			last_event = "mobilize";
			break;

		case PEVNT_DEMOBIL:
			last_event = "demobilize";
			break;

		case PEVNT_REACH:
			last_event = "reachable";
			break;

		case PEVNT_UNREACH:
			last_event = "unreachable";
			break;

		case PEVNT_RESTART:
			last_event = "restart";
			break;

		case PEVNT_REPLY:
			last_event = "no_reply";
			break;

		case PEVNT_RATE:
			last_event = "rate_exceeded";
			break;

		case PEVNT_DENY:
			last_event = "access_denied";
			break;

		case PEVNT_ARMED:
			last_event = "leap_armed";
			break;

		case PEVNT_NEWPEER:
			last_event = "sys_peer";
			break;

		case PEVNT_CLOCK:
			last_event = "clock_alarm";
			break;

		default:
			last_event = "";
			break;
		}
		snprintf(buf, sizeof(buf),
			 "%3d %5u  %04x   %3.3s  %4s  %4.4s %9.9s %11s %2lu",
			 i + 1, assoc_cache[i].assid,
			 assoc_cache[i].status, conf, reach, auth,
			 condition, last_event, event_count);
		bp = buf + strlen(buf);
		while (bp > buf && ' ' == bp[-1])
			--bp;
		bp[0] = '\0';
		fprintf(fp, "%s\n", buf);
	}
}