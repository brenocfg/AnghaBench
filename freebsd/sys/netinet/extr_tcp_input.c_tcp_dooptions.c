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
typedef  int u_char ;
struct tcpopt {int* to_signature; int to_nsacks; int* to_sacks; int to_tfo_len; int* to_tfo_cookie; scalar_t__ to_flags; void* to_tsecr; void* to_tsval; int /*<<< orphan*/  to_wscale; int /*<<< orphan*/  to_mss; } ;

/* Variables and functions */
 int TCPOLEN_MAXSEG ; 
 int TCPOLEN_SACK ; 
 int TCPOLEN_SACK_PERMITTED ; 
 int TCPOLEN_SIGNATURE ; 
 int TCPOLEN_TIMESTAMP ; 
 int TCPOLEN_WINDOW ; 
 int TCPOPT_EOL ; 
#define  TCPOPT_FAST_OPEN 134 
#define  TCPOPT_MAXSEG 133 
 int TCPOPT_NOP ; 
#define  TCPOPT_SACK 132 
#define  TCPOPT_SACK_PERMITTED 131 
#define  TCPOPT_SIGNATURE 130 
#define  TCPOPT_TIMESTAMP 129 
#define  TCPOPT_WINDOW 128 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_MAX_WINSHIFT ; 
 scalar_t__ TOF_FASTOPEN ; 
 scalar_t__ TOF_MSS ; 
 scalar_t__ TOF_SACK ; 
 scalar_t__ TOF_SACKPERM ; 
 scalar_t__ TOF_SCALE ; 
 scalar_t__ TOF_SIGNATURE ; 
 scalar_t__ TOF_TS ; 
 int TO_SYN ; 
 int /*<<< orphan*/  V_tcp_do_sack ; 
 int /*<<< orphan*/  V_tcp_fastopen_client_enable ; 
 int /*<<< orphan*/  V_tcp_fastopen_server_enable ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 void* ntohl (void*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcps_sack_rcv_blocks ; 

void
tcp_dooptions(struct tcpopt *to, u_char *cp, int cnt, int flags)
{
	int opt, optlen;

	to->to_flags = 0;
	for (; cnt > 0; cnt -= optlen, cp += optlen) {
		opt = cp[0];
		if (opt == TCPOPT_EOL)
			break;
		if (opt == TCPOPT_NOP)
			optlen = 1;
		else {
			if (cnt < 2)
				break;
			optlen = cp[1];
			if (optlen < 2 || optlen > cnt)
				break;
		}
		switch (opt) {
		case TCPOPT_MAXSEG:
			if (optlen != TCPOLEN_MAXSEG)
				continue;
			if (!(flags & TO_SYN))
				continue;
			to->to_flags |= TOF_MSS;
			bcopy((char *)cp + 2,
			    (char *)&to->to_mss, sizeof(to->to_mss));
			to->to_mss = ntohs(to->to_mss);
			break;
		case TCPOPT_WINDOW:
			if (optlen != TCPOLEN_WINDOW)
				continue;
			if (!(flags & TO_SYN))
				continue;
			to->to_flags |= TOF_SCALE;
			to->to_wscale = min(cp[2], TCP_MAX_WINSHIFT);
			break;
		case TCPOPT_TIMESTAMP:
			if (optlen != TCPOLEN_TIMESTAMP)
				continue;
			to->to_flags |= TOF_TS;
			bcopy((char *)cp + 2,
			    (char *)&to->to_tsval, sizeof(to->to_tsval));
			to->to_tsval = ntohl(to->to_tsval);
			bcopy((char *)cp + 6,
			    (char *)&to->to_tsecr, sizeof(to->to_tsecr));
			to->to_tsecr = ntohl(to->to_tsecr);
			break;
		case TCPOPT_SIGNATURE:
			/*
			 * In order to reply to a host which has set the
			 * TCP_SIGNATURE option in its initial SYN, we have
			 * to record the fact that the option was observed
			 * here for the syncache code to perform the correct
			 * response.
			 */
			if (optlen != TCPOLEN_SIGNATURE)
				continue;
			to->to_flags |= TOF_SIGNATURE;
			to->to_signature = cp + 2;
			break;
		case TCPOPT_SACK_PERMITTED:
			if (optlen != TCPOLEN_SACK_PERMITTED)
				continue;
			if (!(flags & TO_SYN))
				continue;
			if (!V_tcp_do_sack)
				continue;
			to->to_flags |= TOF_SACKPERM;
			break;
		case TCPOPT_SACK:
			if (optlen <= 2 || (optlen - 2) % TCPOLEN_SACK != 0)
				continue;
			if (flags & TO_SYN)
				continue;
			to->to_flags |= TOF_SACK;
			to->to_nsacks = (optlen - 2) / TCPOLEN_SACK;
			to->to_sacks = cp + 2;
			TCPSTAT_INC(tcps_sack_rcv_blocks);
			break;
		case TCPOPT_FAST_OPEN:
			/*
			 * Cookie length validation is performed by the
			 * server side cookie checking code or the client
			 * side cookie cache update code.
			 */
			if (!(flags & TO_SYN))
				continue;
			if (!V_tcp_fastopen_client_enable &&
			    !V_tcp_fastopen_server_enable)
				continue;
			to->to_flags |= TOF_FASTOPEN;
			to->to_tfo_len = optlen - 2;
			to->to_tfo_cookie = to->to_tfo_len ? cp + 2 : NULL;
			break;
		default:
			continue;
		}
	}
}