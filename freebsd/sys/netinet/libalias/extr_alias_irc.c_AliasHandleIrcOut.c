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
typedef  int u_short ;
typedef  int u_long ;
struct tcphdr {int th_off; int th_x2; scalar_t__ th_sum; int /*<<< orphan*/  th_seq; } ;
struct libalias {int dummy; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct ip {int ip_hl; int ip_len; int /*<<< orphan*/  ip_sum; TYPE_1__ ip_src; } ;
struct in_addr {scalar_t__ s_addr; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddSeq (struct alias_link*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DBprintf (char*) ; 
 int /*<<< orphan*/  DifferentialChecksum (int /*<<< orphan*/ *,int*,int*,int) ; 
 struct alias_link* FindUdpTcpOut (struct libalias*,struct in_addr,struct in_addr,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct in_addr GetAliasAddress (struct alias_link*) ; 
 int GetAliasPort (struct alias_link*) ; 
 int GetDeltaSeqOut (int /*<<< orphan*/ ,struct alias_link*) ; 
 unsigned short IPPORT_RESERVED ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 unsigned int PKTSIZE ; 
 int /*<<< orphan*/  PunchFWHole (struct alias_link*) ; 
 int /*<<< orphan*/  SetAckModified (struct alias_link*) ; 
 scalar_t__ TcpChecksum (struct ip*) ; 
 unsigned long ULONG_MAX ; 
 scalar_t__ htonl (unsigned long) ; 
 int htons (int) ; 
 scalar_t__ ip_next (struct ip*) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 char* newpacket ; 
 int ntohs (int) ; 
 int snprintf (char*,unsigned int,char*,int) ; 

__attribute__((used)) static void
AliasHandleIrcOut(struct libalias *la,
    struct ip *pip,		/* IP packet to examine */
    struct alias_link *lnk,	/* Which link are we on? */
    int maxsize			/* Maximum size of IP packet including
				 * headers */
)
{
	int hlen, tlen, dlen;
	struct in_addr true_addr;
	u_short true_port;
	char *sptr;
	struct tcphdr *tc;
	int i;			/* Iterator through the source */

/* Calculate data length of TCP packet */
	tc = (struct tcphdr *)ip_next(pip);
	hlen = (pip->ip_hl + tc->th_off) << 2;
	tlen = ntohs(pip->ip_len);
	dlen = tlen - hlen;

	/*
	 * Return if data length is too short - assume an entire PRIVMSG in
	 * each packet.
	 */
	if (dlen < (int)sizeof(":A!a@n.n PRIVMSG A :aDCC 1 1a") - 1)
		return;

/* Place string pointer at beginning of data */
	sptr = (char *)pip;
	sptr += hlen;
	maxsize -= hlen;	/* We're interested in maximum size of
				 * data, not packet */

	/* Search for a CTCP command [Note 1] */
	for (i = 0; i < dlen; i++) {
		if (sptr[i] == '\001')
			goto lFOUND_CTCP;
	}
	return;			/* No CTCP commands in  */
	/* Handle CTCP commands - the buffer may have to be copied */
lFOUND_CTCP:
	{
		unsigned int copyat = i;
		unsigned int iCopy = 0;	/* How much data have we written to
					 * copy-back string? */
		unsigned long org_addr;	/* Original IP address */
		unsigned short org_port;	/* Original source port
						 * address */

lCTCP_START:
		if (i >= dlen || iCopy >= PKTSIZE)
			goto lPACKET_DONE;
		newpacket[iCopy++] = sptr[i++];	/* Copy the CTCP start
						 * character */
		/* Start of a CTCP */
		if (i + 4 >= dlen)	/* Too short for DCC */
			goto lBAD_CTCP;
		if (sptr[i + 0] != 'D')
			goto lBAD_CTCP;
		if (sptr[i + 1] != 'C')
			goto lBAD_CTCP;
		if (sptr[i + 2] != 'C')
			goto lBAD_CTCP;
		if (sptr[i + 3] != ' ')
			goto lBAD_CTCP;
		/* We have a DCC command - handle it! */
		i += 4;		/* Skip "DCC " */
		if (iCopy + 4 > PKTSIZE)
			goto lPACKET_DONE;
		newpacket[iCopy++] = 'D';
		newpacket[iCopy++] = 'C';
		newpacket[iCopy++] = 'C';
		newpacket[iCopy++] = ' ';

		DBprintf(("Found DCC\n"));
		/*
		 * Skip any extra spaces (should not occur according to
		 * protocol, but DCC breaks CTCP protocol anyway
		 */
		while (sptr[i] == ' ') {
			if (++i >= dlen) {
				DBprintf(("DCC packet terminated in just spaces\n"));
				goto lPACKET_DONE;
			}
		}

		DBprintf(("Transferring command...\n"));
		while (sptr[i] != ' ') {
			newpacket[iCopy++] = sptr[i];
			if (++i >= dlen || iCopy >= PKTSIZE) {
				DBprintf(("DCC packet terminated during command\n"));
				goto lPACKET_DONE;
			}
		}
		/* Copy _one_ space */
		if (i + 1 < dlen && iCopy < PKTSIZE)
			newpacket[iCopy++] = sptr[i++];

		DBprintf(("Done command - removing spaces\n"));
		/*
		 * Skip any extra spaces (should not occur according to
		 * protocol, but DCC breaks CTCP protocol anyway
		 */
		while (sptr[i] == ' ') {
			if (++i >= dlen) {
				DBprintf(("DCC packet terminated in just spaces (post-command)\n"));
				goto lPACKET_DONE;
			}
		}

		DBprintf(("Transferring filename...\n"));
		while (sptr[i] != ' ') {
			newpacket[iCopy++] = sptr[i];
			if (++i >= dlen || iCopy >= PKTSIZE) {
				DBprintf(("DCC packet terminated during filename\n"));
				goto lPACKET_DONE;
			}
		}
		/* Copy _one_ space */
		if (i + 1 < dlen && iCopy < PKTSIZE)
			newpacket[iCopy++] = sptr[i++];

		DBprintf(("Done filename - removing spaces\n"));
		/*
		 * Skip any extra spaces (should not occur according to
		 * protocol, but DCC breaks CTCP protocol anyway
		 */
		while (sptr[i] == ' ') {
			if (++i >= dlen) {
				DBprintf(("DCC packet terminated in just spaces (post-filename)\n"));
				goto lPACKET_DONE;
			}
		}

		DBprintf(("Fetching IP address\n"));
		/* Fetch IP address */
		org_addr = 0;
		while (i < dlen && isdigit(sptr[i])) {
			if (org_addr > ULONG_MAX / 10UL) {	/* Terminate on overflow */
				DBprintf(("DCC Address overflow (org_addr == 0x%08lx, next char %c\n", org_addr, sptr[i]));
				goto lBAD_CTCP;
			}
			org_addr *= 10;
			org_addr += sptr[i++] - '0';
		}
		DBprintf(("Skipping space\n"));
		if (i + 1 >= dlen || sptr[i] != ' ') {
			DBprintf(("Overflow (%d >= %d) or bad character (%02x) terminating IP address\n", i + 1, dlen, sptr[i]));
			goto lBAD_CTCP;
		}
		/*
		 * Skip any extra spaces (should not occur according to
		 * protocol, but DCC breaks CTCP protocol anyway, so we
		 * might as well play it safe
		 */
		while (sptr[i] == ' ') {
			if (++i >= dlen) {
				DBprintf(("Packet failure - space overflow.\n"));
				goto lPACKET_DONE;
			}
		}
		DBprintf(("Fetching port number\n"));
		/* Fetch source port */
		org_port = 0;
		while (i < dlen && isdigit(sptr[i])) {
			if (org_port > 6554) {	/* Terminate on overflow
						 * (65536/10 rounded up */
				DBprintf(("DCC: port number overflow\n"));
				goto lBAD_CTCP;
			}
			org_port *= 10;
			org_port += sptr[i++] - '0';
		}
		/* Skip illegal addresses (or early termination) */
		if (i >= dlen || (sptr[i] != '\001' && sptr[i] != ' ')) {
			DBprintf(("Bad port termination\n"));
			goto lBAD_CTCP;
		}
		DBprintf(("Got IP %lu and port %u\n", org_addr, (unsigned)org_port));

		/* We've got the address and port - now alias it */
		{
			struct alias_link *dcc_lnk;
			struct in_addr destaddr;


			true_port = htons(org_port);
			true_addr.s_addr = htonl(org_addr);
			destaddr.s_addr = 0;

			/* Sanity/Security checking */
			if (!org_addr || !org_port ||
			    pip->ip_src.s_addr != true_addr.s_addr ||
			    org_port < IPPORT_RESERVED)
				goto lBAD_CTCP;

			/*
			 * Steal the FTP_DATA_PORT - it doesn't really
			 * matter, and this would probably allow it through
			 * at least _some_ firewalls.
			 */
			dcc_lnk = FindUdpTcpOut(la, true_addr, destaddr,
			    true_port, 0,
			    IPPROTO_TCP, 1);
			DBprintf(("Got a DCC link\n"));
			if (dcc_lnk) {
				struct in_addr alias_address;	/* Address from aliasing */
				u_short alias_port;	/* Port given by
							 * aliasing */
				int n;

#ifndef NO_FW_PUNCH
				/* Generate firewall hole as appropriate */
				PunchFWHole(dcc_lnk);
#endif

				alias_address = GetAliasAddress(lnk);
				n = snprintf(&newpacket[iCopy],
				    PKTSIZE - iCopy,
				    "%lu ", (u_long) htonl(alias_address.s_addr));
				if (n < 0) {
					DBprintf(("DCC packet construct failure.\n"));
					goto lBAD_CTCP;
				}
				if ((iCopy += n) >= PKTSIZE) {	/* Truncated/fit exactly
										 * - bad news */
					DBprintf(("DCC constructed packet overflow.\n"));
					goto lBAD_CTCP;
				}
				alias_port = GetAliasPort(dcc_lnk);
				n = snprintf(&newpacket[iCopy],
				    PKTSIZE - iCopy,
				    "%u", htons(alias_port));
				if (n < 0) {
					DBprintf(("DCC packet construct failure.\n"));
					goto lBAD_CTCP;
				}
				iCopy += n;
				/*
				 * Done - truncated cases will be taken
				 * care of by lBAD_CTCP
				 */
				DBprintf(("Aliased IP %lu and port %u\n", alias_address.s_addr, (unsigned)alias_port));
			}
		}
		/*
		 * An uninteresting CTCP - state entered right after '\001'
		 * has been pushed.  Also used to copy the rest of a DCC,
		 * after IP address and port has been handled
		 */
lBAD_CTCP:
		for (; i < dlen && iCopy < PKTSIZE; i++, iCopy++) {
			newpacket[iCopy] = sptr[i];	/* Copy CTCP unchanged */
			if (sptr[i] == '\001') {
				goto lNORMAL_TEXT;
			}
		}
		goto lPACKET_DONE;
		/* Normal text */
lNORMAL_TEXT:
		for (; i < dlen && iCopy < PKTSIZE; i++, iCopy++) {
			newpacket[iCopy] = sptr[i];	/* Copy CTCP unchanged */
			if (sptr[i] == '\001') {
				goto lCTCP_START;
			}
		}
		/* Handle the end of a packet */
lPACKET_DONE:
		iCopy = iCopy > maxsize - copyat ? maxsize - copyat : iCopy;
		memcpy(sptr + copyat, newpacket, iCopy);

/* Save information regarding modified seq and ack numbers */
		{
			int delta;

			SetAckModified(lnk);
			tc = (struct tcphdr *)ip_next(pip);				
			delta = GetDeltaSeqOut(tc->th_seq, lnk);
			AddSeq(lnk, delta + copyat + iCopy - dlen, pip->ip_hl,
			    pip->ip_len, tc->th_seq, tc->th_off);
		}

		/* Revise IP header */
		{
			u_short new_len;

			new_len = htons(hlen + iCopy + copyat);
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
		return;
	}
}