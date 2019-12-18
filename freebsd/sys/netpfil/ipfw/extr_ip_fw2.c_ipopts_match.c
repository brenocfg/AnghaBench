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
struct ip {int ip_hl; } ;
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */
 int IPOPT_EOL ; 
#define  IPOPT_LSRR 131 
 int IPOPT_NOP ; 
 size_t IPOPT_OLEN ; 
 size_t IPOPT_OPTVAL ; 
#define  IPOPT_RR 130 
#define  IPOPT_SSRR 129 
#define  IPOPT_TS 128 
 int IP_FW_IPOPT_LSRR ; 
 int IP_FW_IPOPT_RR ; 
 int IP_FW_IPOPT_SSRR ; 
 int IP_FW_IPOPT_TS ; 
 int flags_match (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ipopts_match(struct ip *ip, ipfw_insn *cmd)
{
	int optlen, bits = 0;
	u_char *cp = (u_char *)(ip + 1);
	int x = (ip->ip_hl << 2) - sizeof (struct ip);

	for (; x > 0; x -= optlen, cp += optlen) {
		int opt = cp[IPOPT_OPTVAL];

		if (opt == IPOPT_EOL)
			break;
		if (opt == IPOPT_NOP)
			optlen = 1;
		else {
			optlen = cp[IPOPT_OLEN];
			if (optlen <= 0 || optlen > x)
				return 0; /* invalid or truncated */
		}
		switch (opt) {

		default:
			break;

		case IPOPT_LSRR:
			bits |= IP_FW_IPOPT_LSRR;
			break;

		case IPOPT_SSRR:
			bits |= IP_FW_IPOPT_SSRR;
			break;

		case IPOPT_RR:
			bits |= IP_FW_IPOPT_RR;
			break;

		case IPOPT_TS:
			bits |= IP_FW_IPOPT_TS;
			break;
		}
	}
	return (flags_match(cmd, bits));
}