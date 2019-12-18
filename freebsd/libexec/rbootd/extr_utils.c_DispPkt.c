#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_hour; int tm_min; int tm_sec; } ;
struct TYPE_17__ {int rmp_retcode; int /*<<< orphan*/  rmp_session; } ;
struct TYPE_16__ {int /*<<< orphan*/  rmp_session; int /*<<< orphan*/  rmp_retcode; int /*<<< orphan*/  rmp_offset; } ;
struct TYPE_15__ {int /*<<< orphan*/  rmp_size; int /*<<< orphan*/  rmp_session; int /*<<< orphan*/  rmp_retcode; int /*<<< orphan*/  rmp_offset; } ;
struct TYPE_14__ {int /*<<< orphan*/  rmp_flnm; int /*<<< orphan*/  rmp_flnmsize; int /*<<< orphan*/  rmp_version; int /*<<< orphan*/  rmp_session; int /*<<< orphan*/  rmp_retcode; int /*<<< orphan*/  rmp_seqno; } ;
struct TYPE_13__ {char* rmp_machtype; int /*<<< orphan*/  rmp_flnm; int /*<<< orphan*/  rmp_flnmsize; int /*<<< orphan*/  rmp_version; int /*<<< orphan*/  rmp_session; int /*<<< orphan*/  rmp_retcode; int /*<<< orphan*/  rmp_seqno; } ;
struct TYPE_12__ {int dsap; int ssap; int /*<<< orphan*/  sxsap; int /*<<< orphan*/  dxsap; int /*<<< orphan*/  cntrl; } ;
struct rmp_packet {int r_type; TYPE_7__ r_done; TYPE_6__ r_rrpl; TYPE_5__ r_rrq; TYPE_4__ r_brpl; TYPE_3__ r_brq; TYPE_2__ hp_llc; } ;
struct TYPE_11__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_18__ {int rmplen; struct rmp_packet rmp; TYPE_1__ tstamp; } ;
typedef  TYPE_8__ RMPCONN ;

/* Variables and functions */
 int DIR_RCVD ; 
 int DIR_SENT ; 
 int /*<<< orphan*/ * DbgFp ; 
 int /*<<< orphan*/  DspFlnm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* EnetStr (TYPE_8__*) ; 
 int /*<<< orphan*/  GETWORD (int /*<<< orphan*/ ,int) ; 
 char* IntfName ; 
 int RMPREADSIZE (int /*<<< orphan*/ ) ; 
#define  RMP_BOOT_DONE 132 
#define  RMP_BOOT_REPL 131 
#define  RMP_BOOT_REQ 130 
 int RMP_MACHLEN ; 
 int RMP_PROBESID ; 
#define  RMP_READ_REPL 129 
#define  RMP_READ_REQ 128 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  WORDZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char const*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int sigblock (int) ; 
 int sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (int) ; 

void
DispPkt(RMPCONN *rconn, int direct)
{
	static const char BootFmt[] = "\t\tRetCode:%u SeqNo:%x SessID:%x Vers:%u";
	static const char ReadFmt[] = "\t\tRetCode:%u Offset:%x SessID:%x\n";

	struct tm *tmp;
	struct rmp_packet *rmp;
	int i, omask;
	u_int32_t t;

	/*
	 *  Since we will be working with RmpConns as well as DbgFp, we
	 *  must block signals that can affect either.
	 */
	omask = sigblock(sigmask(SIGHUP)|sigmask(SIGUSR1)|sigmask(SIGUSR2));

	if (DbgFp == NULL) {			/* sanity */
		(void) sigsetmask(omask);
		return;
	}

	/* display direction packet is going using '>>>' or '<<<' */
	fputs((direct==DIR_RCVD)?"<<< ":(direct==DIR_SENT)?">>> ":"", DbgFp);

	/* display packet timestamp */
	tmp = localtime((time_t *)&rconn->tstamp.tv_sec);
	fprintf(DbgFp, "%02d:%02d:%02d.%06ld   ", tmp->tm_hour, tmp->tm_min,
	        tmp->tm_sec, rconn->tstamp.tv_usec);

	/* display src or dst addr and information about network interface */
	fprintf(DbgFp, "Addr: %s   Intf: %s\n", EnetStr(rconn), IntfName);

	rmp = &rconn->rmp;

	/* display IEEE 802.2 Logical Link Control header */
	(void) fprintf(DbgFp, "\t802.2 LLC: DSAP:%x SSAP:%x CTRL:%x\n",
               rmp->hp_llc.dsap, rmp->hp_llc.ssap, ntohs(rmp->hp_llc.cntrl));

	/* display HP extensions to 802.2 Logical Link Control header */
	(void) fprintf(DbgFp, "\tHP Ext:    DXSAP:%x SXSAP:%x\n",
	               ntohs(rmp->hp_llc.dxsap), ntohs(rmp->hp_llc.sxsap));

	/*
	 *  Display information about RMP packet using type field to
	 *  determine what kind of packet this is.
	 */
	switch(rmp->r_type) {
		case RMP_BOOT_REQ:		/* boot request */
			(void) fprintf(DbgFp, "\tBoot Request:");
			GETWORD(rmp->r_brq.rmp_seqno, t);
			if (ntohs(rmp->r_brq.rmp_session) == RMP_PROBESID) {
				if (WORDZE(rmp->r_brq.rmp_seqno))
					fputs(" (Send Server ID)", DbgFp);
				else
					fprintf(DbgFp," (Send Filename #%u)",t);
			}
			(void) fputc('\n', DbgFp);
			(void) fprintf(DbgFp, BootFmt, rmp->r_brq.rmp_retcode,
			        t, ntohs(rmp->r_brq.rmp_session),
			        ntohs(rmp->r_brq.rmp_version));
			(void) fprintf(DbgFp, "\n\t\tMachine Type: ");
			for (i = 0; i < RMP_MACHLEN; i++)
				(void) fputc(rmp->r_brq.rmp_machtype[i], DbgFp);
			DspFlnm(rmp->r_brq.rmp_flnmsize, &rmp->r_brq.rmp_flnm);
			break;
		case RMP_BOOT_REPL:		/* boot reply */
			fprintf(DbgFp, "\tBoot Reply:\n");
			GETWORD(rmp->r_brpl.rmp_seqno, t);
			(void) fprintf(DbgFp, BootFmt, rmp->r_brpl.rmp_retcode,
			        t, ntohs(rmp->r_brpl.rmp_session),
			        ntohs(rmp->r_brpl.rmp_version));
			DspFlnm(rmp->r_brpl.rmp_flnmsize,&rmp->r_brpl.rmp_flnm);
			break;
		case RMP_READ_REQ:		/* read request */
			(void) fprintf(DbgFp, "\tRead Request:\n");
			GETWORD(rmp->r_rrq.rmp_offset, t);
			(void) fprintf(DbgFp, ReadFmt, rmp->r_rrq.rmp_retcode,
			        t, ntohs(rmp->r_rrq.rmp_session));
			(void) fprintf(DbgFp, "\t\tNoOfBytes: %u\n",
			        ntohs(rmp->r_rrq.rmp_size));
			break;
		case RMP_READ_REPL:		/* read reply */
			(void) fprintf(DbgFp, "\tRead Reply:\n");
			GETWORD(rmp->r_rrpl.rmp_offset, t);
			(void) fprintf(DbgFp, ReadFmt, rmp->r_rrpl.rmp_retcode,
			        t, ntohs(rmp->r_rrpl.rmp_session));
			(void) fprintf(DbgFp, "\t\tNoOfBytesSent: %zu\n",
			        rconn->rmplen - RMPREADSIZE(0));
			break;
		case RMP_BOOT_DONE:		/* boot complete */
			(void) fprintf(DbgFp, "\tBoot Complete:\n");
			(void) fprintf(DbgFp, "\t\tRetCode:%u SessID:%x\n",
			        rmp->r_done.rmp_retcode,
			        ntohs(rmp->r_done.rmp_session));
			break;
		default:			/* ??? */
			(void) fprintf(DbgFp, "\tUnknown Type:(%d)\n",
				rmp->r_type);
	}
	(void) fputc('\n', DbgFp);
	(void) fflush(DbgFp);

	(void) sigsetmask(omask);		/* reset old signal mask */
}