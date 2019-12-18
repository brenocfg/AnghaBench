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
struct tcphdr {int th_off; int /*<<< orphan*/  th_dport; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct libalias {TYPE_1__ true_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct ip {int ip_hl; int /*<<< orphan*/  ip_len; TYPE_2__ ip_src; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 int FTP_227_REPLY ; 
 int FTP_229_REPLY ; 
 scalar_t__ FTP_CONTROL_PORT_NUMBER ; 
 int FTP_EPRT_COMMAND ; 
 int FTP_PORT_COMMAND ; 
 int FTP_UNKNOWN_MESSAGE ; 
 int GetProtocolFlags (struct alias_link*) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  NewFtpMessage (struct libalias*,struct ip*,struct alias_link*,int,int) ; 
 scalar_t__ ParseFtp227Reply (struct libalias*,char*,int) ; 
 scalar_t__ ParseFtp229Reply (struct libalias*,char*,int) ; 
 scalar_t__ ParseFtpEprtCommand (struct libalias*,char*,int) ; 
 scalar_t__ ParseFtpPortCommand (struct libalias*,char*,int) ; 
 int /*<<< orphan*/  SetProtocolFlags (struct alias_link*,int) ; 
 int WAIT_CRLF ; 
 scalar_t__ ip_next (struct ip*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AliasHandleFtpOut(
    struct libalias *la,
    struct ip *pip,		/* IP packet to examine/patch */
    struct alias_link *lnk,	/* The link to go through (aliased port) */
    int maxpacketsize		/* The maximum size this packet can grow to
	(including headers) */ )
{
	int hlen, tlen, dlen, pflags;
	char *sptr;
	struct tcphdr *tc;
	int ftp_message_type;

/* Calculate data length of TCP packet */
	tc = (struct tcphdr *)ip_next(pip);
	hlen = (pip->ip_hl + tc->th_off) << 2;
	tlen = ntohs(pip->ip_len);
	dlen = tlen - hlen;

/* Place string pointer and beginning of data */
	sptr = (char *)pip;
	sptr += hlen;

/*
 * Check that data length is not too long and previous message was
 * properly terminated with CRLF.
 */
	pflags = GetProtocolFlags(lnk);
	if (dlen <= MAX_MESSAGE_SIZE && !(pflags & WAIT_CRLF)) {
		ftp_message_type = FTP_UNKNOWN_MESSAGE;

		if (ntohs(tc->th_dport) == FTP_CONTROL_PORT_NUMBER) {
/*
 * When aliasing a client, check for the PORT/EPRT command.
 */
			if (ParseFtpPortCommand(la, sptr, dlen))
				ftp_message_type = FTP_PORT_COMMAND;
			else if (ParseFtpEprtCommand(la, sptr, dlen))
				ftp_message_type = FTP_EPRT_COMMAND;
		} else {
/*
 * When aliasing a server, check for the 227/229 reply.
 */
			if (ParseFtp227Reply(la, sptr, dlen))
				ftp_message_type = FTP_227_REPLY;
			else if (ParseFtp229Reply(la, sptr, dlen)) {
				ftp_message_type = FTP_229_REPLY;
				la->true_addr.s_addr = pip->ip_src.s_addr;
			}
		}

		if (ftp_message_type != FTP_UNKNOWN_MESSAGE)
			NewFtpMessage(la, pip, lnk, maxpacketsize, ftp_message_type);
	}
/* Track the msgs which are CRLF term'd for PORT/PASV FW breach */

	if (dlen) {		/* only if there's data */
		sptr = (char *)pip;	/* start over at beginning */
		tlen = ntohs(pip->ip_len);	/* recalc tlen, pkt may
						 * have grown */
		if (sptr[tlen - 2] == '\r' && sptr[tlen - 1] == '\n')
			pflags &= ~WAIT_CRLF;
		else
			pflags |= WAIT_CRLF;
		SetProtocolFlags(lnk, pflags);
	}
}