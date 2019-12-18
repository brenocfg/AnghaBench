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
typedef  int u_short ;
struct tcphdr {int th_x2; scalar_t__ th_sum; int /*<<< orphan*/  th_off; int /*<<< orphan*/  th_seq; } ;
struct libalias {int dummy; } ;
struct ip {int ip_len; int /*<<< orphan*/  ip_sum; int /*<<< orphan*/  ip_hl; int /*<<< orphan*/  ip_src; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddSeq (struct alias_link*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DifferentialChecksum (int /*<<< orphan*/ *,int*,int*,int) ; 
 int /*<<< orphan*/  FindAliasAddress (struct libalias*,int /*<<< orphan*/ ) ; 
 int FindNewPortGroup (struct libalias*,struct in_addr,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct alias_link* FindRtspOut (struct libalias*,int /*<<< orphan*/ ,struct in_addr,int,int,int /*<<< orphan*/ ) ; 
 int GetDeltaSeqOut (int /*<<< orphan*/ ,struct alias_link*) ; 
 int /*<<< orphan*/  GetOriginalAddress (struct alias_link*) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  ISDIGIT (char) ; 
 int /*<<< orphan*/  PunchFWHole (struct alias_link*) ; 
 int RTSP_PORT_GROUP ; 
 int /*<<< orphan*/  SetAckModified (struct alias_link*) ; 
 scalar_t__ TcpChecksum (struct ip*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int htons (int) ; 
 scalar_t__ ip_next (struct ip*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int ntohs (int) ; 
 int search_string (char*,int,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
alias_rtsp_out(struct libalias *la, struct ip *pip,
    struct alias_link *lnk,
    char *data,
    const char *port_str)
{
	int hlen, tlen, dlen;
	struct tcphdr *tc;
	int i, j, pos, state, port_dlen, new_dlen, delta;
	u_short p[2], new_len;
	u_short sport, eport, base_port;
	u_short salias = 0, ealias = 0, base_alias = 0;
	const char *transport_str = "transport:";
	char newdata[2048], *port_data, *port_newdata, stemp[80];
	int links_created = 0, pkt_updated = 0;
	struct alias_link *rtsp_lnk = NULL;
	struct in_addr null_addr;

	/* Calculate data length of TCP packet */
	tc = (struct tcphdr *)ip_next(pip);
	hlen = (pip->ip_hl + tc->th_off) << 2;
	tlen = ntohs(pip->ip_len);
	dlen = tlen - hlen;

	/* Find keyword, "Transport: " */
	pos = search_string(data, dlen, transport_str);
	if (pos < 0) {
		return (-1);
	}
	port_data = data + pos;
	port_dlen = dlen - pos;

	memcpy(newdata, data, pos);
	port_newdata = newdata + pos;

	while (port_dlen > (int)strlen(port_str)) {
		/* Find keyword, appropriate port string */
		pos = search_string(port_data, port_dlen, port_str);
		if (pos < 0) {
			break;
		}
		memcpy(port_newdata, port_data, pos + 1);
		port_newdata += (pos + 1);

		p[0] = p[1] = 0;
		sport = eport = 0;
		state = 0;
		for (i = pos; i < port_dlen; i++) {
			switch (state) {
			case 0:
				if (port_data[i] == '=') {
					state++;
				}
				break;
			case 1:
				if (ISDIGIT(port_data[i])) {
					p[0] = p[0] * 10 + port_data[i] - '0';
				} else {
					if (port_data[i] == ';') {
						state = 3;
					}
					if (port_data[i] == '-') {
						state++;
					}
				}
				break;
			case 2:
				if (ISDIGIT(port_data[i])) {
					p[1] = p[1] * 10 + port_data[i] - '0';
				} else {
					state++;
				}
				break;
			case 3:
				base_port = p[0];
				sport = htons(p[0]);
				eport = htons(p[1]);

				if (!links_created) {

					links_created = 1;
					/*
					 * Find an even numbered port
					 * number base that satisfies the
					 * contiguous number of ports we
					 * need
					 */
					null_addr.s_addr = 0;
					if (0 == (salias = FindNewPortGroup(la, null_addr,
					    FindAliasAddress(la, pip->ip_src),
					    sport, 0,
					    RTSP_PORT_GROUP,
					    IPPROTO_UDP, 1))) {
#ifdef LIBALIAS_DEBUG
						fprintf(stderr,
						    "PacketAlias/RTSP: Cannot find contiguous RTSP data ports\n");
#endif
					} else {

						base_alias = ntohs(salias);
						for (j = 0; j < RTSP_PORT_GROUP; j++) {
							/*
							 * Establish link
							 * to port found in
							 * RTSP packet
							 */
							rtsp_lnk = FindRtspOut(la, GetOriginalAddress(lnk), null_addr,
							    htons(base_port + j), htons(base_alias + j),
							    IPPROTO_UDP);
							if (rtsp_lnk != NULL) {
#ifndef NO_FW_PUNCH
								/*
								 * Punch
								 * hole in
								 * firewall
								 */
								PunchFWHole(rtsp_lnk);
#endif
							} else {
#ifdef LIBALIAS_DEBUG
								fprintf(stderr,
								    "PacketAlias/RTSP: Cannot allocate RTSP data ports\n");
#endif
								break;
							}
						}
					}
					ealias = htons(base_alias + (RTSP_PORT_GROUP - 1));
				}
				if (salias && rtsp_lnk) {

					pkt_updated = 1;

					/* Copy into IP packet */
					sprintf(stemp, "%d", ntohs(salias));
					memcpy(port_newdata, stemp, strlen(stemp));
					port_newdata += strlen(stemp);

					if (eport != 0) {
						*port_newdata = '-';
						port_newdata++;

						/* Copy into IP packet */
						sprintf(stemp, "%d", ntohs(ealias));
						memcpy(port_newdata, stemp, strlen(stemp));
						port_newdata += strlen(stemp);
					}
					*port_newdata = ';';
					port_newdata++;
				}
				state++;
				break;
			}
			if (state > 3) {
				break;
			}
		}
		port_data += i;
		port_dlen -= i;
	}

	if (!pkt_updated)
		return (-1);

	memcpy(port_newdata, port_data, port_dlen);
	port_newdata += port_dlen;
	*port_newdata = '\0';

	/* Create new packet */
	new_dlen = port_newdata - newdata;
	memcpy(data, newdata, new_dlen);

	SetAckModified(lnk);
	tc = (struct tcphdr *)ip_next(pip);
	delta = GetDeltaSeqOut(tc->th_seq, lnk);
	AddSeq(lnk, delta + new_dlen - dlen, pip->ip_hl, pip->ip_len,
	    tc->th_seq, tc->th_off);

	new_len = htons(hlen + new_dlen);
	DifferentialChecksum(&pip->ip_sum,
	    &new_len,
	    &pip->ip_len,
	    1);
	pip->ip_len = new_len;

	tc->th_sum = 0;
#ifdef _KERNEL
	tc->th_x2 = 1;
#else
	tc->th_sum = TcpChecksum(pip);
#endif
	return (0);
}