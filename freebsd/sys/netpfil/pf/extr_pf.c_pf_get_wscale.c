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
typedef  int u_int8_t ;
typedef  int u_int16_t ;
struct tcphdr {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int PF_WSCALE_FLAG ; 
#define  TCPOPT_EOL 130 
#define  TCPOPT_NOP 129 
#define  TCPOPT_WINDOW 128 
 int TCP_MAX_WINSHIFT ; 
 int /*<<< orphan*/  pf_pull_hdr (struct mbuf*,int,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int8_t
pf_get_wscale(struct mbuf *m, int off, u_int16_t th_off, sa_family_t af)
{
	int		 hlen;
	u_int8_t	 hdr[60];
	u_int8_t	*opt, optlen;
	u_int8_t	 wscale = 0;

	hlen = th_off << 2;		/* hlen <= sizeof(hdr) */
	if (hlen <= sizeof(struct tcphdr))
		return (0);
	if (!pf_pull_hdr(m, off, hdr, hlen, NULL, NULL, af))
		return (0);
	opt = hdr + sizeof(struct tcphdr);
	hlen -= sizeof(struct tcphdr);
	while (hlen >= 3) {
		switch (*opt) {
		case TCPOPT_EOL:
		case TCPOPT_NOP:
			++opt;
			--hlen;
			break;
		case TCPOPT_WINDOW:
			wscale = opt[2];
			if (wscale > TCP_MAX_WINSHIFT)
				wscale = TCP_MAX_WINSHIFT;
			wscale |= PF_WSCALE_FLAG;
			/* FALLTHROUGH */
		default:
			optlen = opt[1];
			if (optlen < 2)
				optlen = 2;
			hlen -= optlen;
			opt += optlen;
			break;
		}
	}
	return (wscale);
}