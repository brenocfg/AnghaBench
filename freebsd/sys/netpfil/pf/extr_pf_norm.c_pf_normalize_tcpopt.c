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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int u_char ;
struct tcphdr {int th_off; int /*<<< orphan*/  th_sum; } ;
struct pf_rule {int /*<<< orphan*/  max_mss; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int TCPOPT_EOL ; 
#define  TCPOPT_MAXSEG 128 
 int TCPOPT_NOP ; 
 int TCP_MAXOLEN ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_copyback (struct mbuf*,int,int,int*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_proto_cksum_fixup (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_pull_hdr (struct mbuf*,int,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pf_normalize_tcpopt(struct pf_rule *r, struct mbuf *m, struct tcphdr *th,
    int off, sa_family_t af)
{
	u_int16_t	*mss;
	int		 thoff;
	int		 opt, cnt, optlen = 0;
	int		 rewrite = 0;
	u_char		 opts[TCP_MAXOLEN];
	u_char		*optp = opts;

	thoff = th->th_off << 2;
	cnt = thoff - sizeof(struct tcphdr);

	if (cnt > 0 && !pf_pull_hdr(m, off + sizeof(*th), opts, cnt,
	    NULL, NULL, af))
		return (rewrite);

	for (; cnt > 0; cnt -= optlen, optp += optlen) {
		opt = optp[0];
		if (opt == TCPOPT_EOL)
			break;
		if (opt == TCPOPT_NOP)
			optlen = 1;
		else {
			if (cnt < 2)
				break;
			optlen = optp[1];
			if (optlen < 2 || optlen > cnt)
				break;
		}
		switch (opt) {
		case TCPOPT_MAXSEG:
			mss = (u_int16_t *)(optp + 2);
			if ((ntohs(*mss)) > r->max_mss) {
				th->th_sum = pf_proto_cksum_fixup(m,
				    th->th_sum, *mss, htons(r->max_mss), 0);
				*mss = htons(r->max_mss);
				rewrite = 1;
			}
			break;
		default:
			break;
		}
	}

	if (rewrite)
		m_copyback(m, off + sizeof(*th), thoff - sizeof(*th), opts);

	return (rewrite);
}