#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_char ;
struct tcphdr {int th_off; int th_x2; scalar_t__ th_sum; int /*<<< orphan*/  th_seq; } ;
struct TYPE_4__ {scalar_t__ s_addr; } ;
struct libalias {scalar_t__ true_port; TYPE_2__ true_addr; } ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct ip {int ip_hl; int /*<<< orphan*/  ip_len; int /*<<< orphan*/  ip_sum; TYPE_1__ ip_src; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 struct alias_link* AddLink (struct libalias*,TYPE_2__,int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddSeq (struct alias_link*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DifferentialChecksum (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
#define  FTP_227_REPLY 131 
#define  FTP_229_REPLY 130 
#define  FTP_EPRT_COMMAND 129 
#define  FTP_PORT_COMMAND 128 
 int /*<<< orphan*/  GET_ALIAS_PORT ; 
 struct in_addr GetAliasAddress (struct alias_link*) ; 
 int /*<<< orphan*/  GetAliasPort (struct alias_link*) ; 
 int GetDeltaSeqOut (int /*<<< orphan*/ ,struct alias_link*) ; 
 int /*<<< orphan*/  GetDestAddress (struct alias_link*) ; 
 scalar_t__ IPPORT_RESERVED ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  PunchFWHole (struct alias_link*) ; 
 int /*<<< orphan*/  SetAckModified (struct alias_link*) ; 
 scalar_t__ TcpChecksum (struct ip*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ ip_next (struct ip*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void
NewFtpMessage(struct libalias *la, struct ip *pip,
    struct alias_link *lnk,
    int maxpacketsize,
    int ftp_message_type)
{
	struct alias_link *ftp_lnk;

/* Security checks. */
	if (pip->ip_src.s_addr != la->true_addr.s_addr)
		return;

	if (la->true_port < IPPORT_RESERVED)
		return;

	/* Establish link to address and port found in FTP control message. */
	ftp_lnk = AddLink(la, la->true_addr, GetDestAddress(lnk),
	    GetAliasAddress(lnk), htons(la->true_port), 0, GET_ALIAS_PORT,
	    IPPROTO_TCP);

	if (ftp_lnk != NULL) {
		int slen, hlen, tlen, dlen;
		struct tcphdr *tc;

#ifndef NO_FW_PUNCH
		/* Punch hole in firewall */
		PunchFWHole(ftp_lnk);
#endif

/* Calculate data length of TCP packet */
		tc = (struct tcphdr *)ip_next(pip);
		hlen = (pip->ip_hl + tc->th_off) << 2;
		tlen = ntohs(pip->ip_len);
		dlen = tlen - hlen;

/* Create new FTP message. */
		{
			char stemp[MAX_MESSAGE_SIZE + 1];
			char *sptr;
			u_short alias_port;
			u_char *ptr;
			int a1, a2, a3, a4, p1, p2;
			struct in_addr alias_address;

/* Decompose alias address into quad format */
			alias_address = GetAliasAddress(lnk);
			ptr = (u_char *) & alias_address.s_addr;
			a1 = *ptr++;
			a2 = *ptr++;
			a3 = *ptr++;
			a4 = *ptr;

			alias_port = GetAliasPort(ftp_lnk);

/* Prepare new command */
			switch (ftp_message_type) {
			case FTP_PORT_COMMAND:
			case FTP_227_REPLY:
				/* Decompose alias port into pair format. */
				ptr = (char *)&alias_port;
				p1 = *ptr++;
				p2 = *ptr;

				if (ftp_message_type == FTP_PORT_COMMAND) {
					/* Generate PORT command string. */
					sprintf(stemp, "PORT %d,%d,%d,%d,%d,%d\r\n",
					    a1, a2, a3, a4, p1, p2);
				} else {
					/* Generate 227 reply string. */
					sprintf(stemp,
					    "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)\r\n",
					    a1, a2, a3, a4, p1, p2);
				}
				break;
			case FTP_EPRT_COMMAND:
				/* Generate EPRT command string. */
				sprintf(stemp, "EPRT |1|%d.%d.%d.%d|%d|\r\n",
				    a1, a2, a3, a4, ntohs(alias_port));
				break;
			case FTP_229_REPLY:
				/* Generate 229 reply string. */
				sprintf(stemp, "229 Entering Extended Passive Mode (|||%d|)\r\n",
				    ntohs(alias_port));
				break;
			}

/* Save string length for IP header modification */
			slen = strlen(stemp);

/* Copy modified buffer into IP packet. */
			sptr = (char *)pip;
			sptr += hlen;
			strncpy(sptr, stemp, maxpacketsize - hlen);
		}

/* Save information regarding modified seq and ack numbers */
		{
			int delta;

			SetAckModified(lnk);
			tc = (struct tcphdr *)ip_next(pip);				
			delta = GetDeltaSeqOut(tc->th_seq, lnk);
			AddSeq(lnk, delta + slen - dlen, pip->ip_hl, 
			    pip->ip_len, tc->th_seq, tc->th_off);
		}

/* Revise IP header */
		{
			u_short new_len;

			new_len = htons(hlen + slen);
			DifferentialChecksum(&pip->ip_sum,
			    &new_len,
			    &pip->ip_len,
			    1);
			pip->ip_len = new_len;
		}

/* Compute TCP checksum for revised packet */
		tc->th_sum = 0;
#ifdef _KERNEL
		tc->th_x2 = 1;
#else
		tc->th_sum = TcpChecksum(pip);
#endif
	} else {
#ifdef LIBALIAS_DEBUG
		fprintf(stderr,
		    "PacketAlias/HandleFtpOut: Cannot allocate FTP data port\n");
#endif
	}
}