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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_char ;
struct tcphdr {int th_off; } ;

/* Variables and functions */
 int IP_FW_TCPOPT_MSS ; 
 int IP_FW_TCPOPT_SACK ; 
 int IP_FW_TCPOPT_TS ; 
 int IP_FW_TCPOPT_WINDOW ; 
 int TCPOPT_EOL ; 
#define  TCPOPT_MAXSEG 132 
 int TCPOPT_NOP ; 
#define  TCPOPT_SACK 131 
#define  TCPOPT_SACK_PERMITTED 130 
#define  TCPOPT_TIMESTAMP 129 
#define  TCPOPT_WINDOW 128 
 int /*<<< orphan*/  be16dec (int*) ; 

__attribute__((used)) static int
tcpopts_parse(struct tcphdr *tcp, uint16_t *mss)
{
	u_char *cp = (u_char *)(tcp + 1);
	int optlen, bits = 0;
	int x = (tcp->th_off << 2) - sizeof(struct tcphdr);

	for (; x > 0; x -= optlen, cp += optlen) {
		int opt = cp[0];
		if (opt == TCPOPT_EOL)
			break;
		if (opt == TCPOPT_NOP)
			optlen = 1;
		else {
			optlen = cp[1];
			if (optlen <= 0)
				break;
		}

		switch (opt) {
		default:
			break;

		case TCPOPT_MAXSEG:
			bits |= IP_FW_TCPOPT_MSS;
			if (mss != NULL)
				*mss = be16dec(cp + 2);
			break;

		case TCPOPT_WINDOW:
			bits |= IP_FW_TCPOPT_WINDOW;
			break;

		case TCPOPT_SACK_PERMITTED:
		case TCPOPT_SACK:
			bits |= IP_FW_TCPOPT_SACK;
			break;

		case TCPOPT_TIMESTAMP:
			bits |= IP_FW_TCPOPT_TS;
			break;
		}
	}
	return (bits);
}