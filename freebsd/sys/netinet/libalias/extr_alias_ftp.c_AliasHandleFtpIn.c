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
struct tcphdr {int th_off; int /*<<< orphan*/  th_dport; } ;
struct libalias {scalar_t__ true_port; int /*<<< orphan*/  true_addr; } ;
struct ip {int ip_hl; int /*<<< orphan*/  ip_len; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddLink (struct libalias*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FTP_CONTROL_PORT_NUMBER ; 
 int /*<<< orphan*/  GET_ALIAS_PORT ; 
 int /*<<< orphan*/  GetAliasAddress (struct alias_link*) ; 
 int /*<<< orphan*/  GetOriginalAddress (struct alias_link*) ; 
 int GetProtocolFlags (struct alias_link*) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int MAX_MESSAGE_SIZE ; 
 scalar_t__ ParseFtpEprtCommand (struct libalias*,char*,int) ; 
 scalar_t__ ParseFtpPortCommand (struct libalias*,char*,int) ; 
 int /*<<< orphan*/  SetProtocolFlags (struct alias_link*,int) ; 
 int WAIT_CRLF ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 scalar_t__ ip_next (struct ip*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AliasHandleFtpIn(struct libalias *la,
    struct ip *pip,		/* IP packet to examine/patch */
    struct alias_link *lnk)	/* The link to go through (aliased port) */
{
	int hlen, tlen, dlen, pflags;
	char *sptr;
	struct tcphdr *tc;

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
	if (dlen <= MAX_MESSAGE_SIZE && (pflags & WAIT_CRLF) == 0 &&
	    ntohs(tc->th_dport) == FTP_CONTROL_PORT_NUMBER &&
	    (ParseFtpPortCommand(la, sptr, dlen) != 0 ||
	     ParseFtpEprtCommand(la, sptr, dlen) != 0)) {
		/*
		 * Alias active mode client requesting data from server
		 * behind NAT.  We need to alias server->client connection
		 * to external address client is connecting to.
		 */
		AddLink(la, GetOriginalAddress(lnk), la->true_addr,
		    GetAliasAddress(lnk), htons(FTP_CONTROL_PORT_NUMBER - 1),
		    htons(la->true_port), GET_ALIAS_PORT, IPPROTO_TCP);
	}
	/* Track the msgs which are CRLF term'd for PORT/PASV FW breach */
	if (dlen) {
		sptr = (char *)pip;		/* start over at beginning */
		tlen = ntohs(pip->ip_len);	/* recalc tlen, pkt may
						 * have grown.
						 */
		if (sptr[tlen - 2] == '\r' && sptr[tlen - 1] == '\n')
			pflags &= ~WAIT_CRLF;
		else
			pflags |= WAIT_CRLF;
		SetProtocolFlags(lnk, pflags);
       }
}