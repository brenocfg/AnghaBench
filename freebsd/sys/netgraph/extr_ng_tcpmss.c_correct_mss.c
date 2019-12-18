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
typedef  int uint16_t ;
typedef  scalar_t__ u_char ;
struct tcphdr {scalar_t__ th_sum; } ;

/* Variables and functions */
 int CSUM_TCP ; 
 int /*<<< orphan*/  TCPMSS_ADJUST_CHECKSUM (int,int) ; 
 int TCPOLEN_MAXSEG ; 
 scalar_t__ TCPOPT_EOL ; 
 scalar_t__ TCPOPT_MAXSEG ; 
 scalar_t__ TCPOPT_NOP ; 
 int be16dec (scalar_t__*) ; 
 int /*<<< orphan*/  be16enc (scalar_t__*,int) ; 

__attribute__((used)) static int
correct_mss(struct tcphdr *tc, int hlen, uint16_t maxmss, int flags)
{
	int olen, optlen;
	u_char *opt;
	int accumulate;
	int res = 0;
	uint16_t sum;

	for (olen = hlen - sizeof(struct tcphdr), opt = (u_char *)(tc + 1);
	     olen > 0; olen -= optlen, opt += optlen) {
		if (*opt == TCPOPT_EOL)
			break;
		else if (*opt == TCPOPT_NOP)
			optlen = 1;
		else {
			optlen = *(opt + 1);
			if (optlen <= 0 || optlen > olen)
				break;
			if (*opt == TCPOPT_MAXSEG) {
				if (optlen != TCPOLEN_MAXSEG)
					continue;
				accumulate = be16dec(opt + 2);
				if (accumulate > maxmss) {
					if ((flags & CSUM_TCP) == 0) {
						accumulate -= maxmss;
						sum = be16dec(&tc->th_sum);
						TCPMSS_ADJUST_CHECKSUM(accumulate, sum);
						be16enc(&tc->th_sum, sum);
					}
					be16enc(opt + 2, maxmss);
					res = 1;
				}
			}
		}
	}
	return (res);
}