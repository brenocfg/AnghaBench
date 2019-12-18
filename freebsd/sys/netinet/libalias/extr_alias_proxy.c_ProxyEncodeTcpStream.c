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
typedef  int u_int ;
struct tcphdr {int th_off; int th_x2; scalar_t__ th_sum; int /*<<< orphan*/  th_seq; } ;
struct ip {int ip_len; int ip_hl; int /*<<< orphan*/  ip_sum; } ;
struct alias_link {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_CHECKSUM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddSeq (struct alias_link*,int,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GetAckModified (struct alias_link*) ; 
 int GetDeltaSeqOut (int /*<<< orphan*/ ,struct alias_link*) ; 
 int /*<<< orphan*/  GetProxyAddress (struct alias_link*) ; 
 int GetProxyPort (struct alias_link*) ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  INET_NTOA_BUF (char*) ; 
 int /*<<< orphan*/  SetAckModified (struct alias_link*) ; 
 scalar_t__ TcpChecksum (struct ip*) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int htons (int) ; 
 char* inet_ntoa_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ip_next (struct ip*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
ProxyEncodeTcpStream(struct alias_link *lnk,
    struct ip *pip,
    int maxpacketsize)
{
	int slen;
	char buffer[40];
	struct tcphdr *tc;
	char addrbuf[INET_ADDRSTRLEN];

/* Compute pointer to tcp header */
	tc = (struct tcphdr *)ip_next(pip);

/* Don't modify if once already modified */

	if (GetAckModified(lnk))
		return;

/* Translate destination address and port to string form */
	snprintf(buffer, sizeof(buffer) - 2, "[DEST %s %d]",
	    inet_ntoa_r(GetProxyAddress(lnk), INET_NTOA_BUF(addrbuf)),
	    (u_int) ntohs(GetProxyPort(lnk)));

/* Pad string out to a multiple of two in length */
	slen = strlen(buffer);
	switch (slen % 2) {
	case 0:
		strcat(buffer, " \n");
		slen += 2;
		break;
	case 1:
		strcat(buffer, "\n");
		slen += 1;
	}

/* Check for packet overflow */
	if ((int)(ntohs(pip->ip_len) + strlen(buffer)) > maxpacketsize)
		return;

/* Shift existing TCP data and insert destination string */
	{
		int dlen;
		int hlen;
		char *p;

		hlen = (pip->ip_hl + tc->th_off) << 2;
		dlen = ntohs(pip->ip_len) - hlen;

/* Modify first packet that has data in it */

		if (dlen == 0)
			return;

		p = (char *)pip;
		p += hlen;

		bcopy(p, p + slen, dlen);
		memcpy(p, buffer, slen);
	}

/* Save information about modfied sequence number */
	{
		int delta;

		SetAckModified(lnk);
		tc = (struct tcphdr *)ip_next(pip);			
		delta = GetDeltaSeqOut(tc->th_seq, lnk);
		AddSeq(lnk, delta + slen, pip->ip_hl, pip->ip_len, tc->th_seq,
		    tc->th_off);
	}

/* Update IP header packet length and checksum */
	{
		int accumulate;

		accumulate = pip->ip_len;
		pip->ip_len = htons(ntohs(pip->ip_len) + slen);
		accumulate -= pip->ip_len;

		ADJUST_CHECKSUM(accumulate, pip->ip_sum);
	}

/* Update TCP checksum, Use TcpChecksum since so many things have
   already changed. */

	tc->th_sum = 0;
#ifdef _KERNEL
	tc->th_x2 = 1;
#else
	tc->th_sum = TcpChecksum(pip);
#endif
}