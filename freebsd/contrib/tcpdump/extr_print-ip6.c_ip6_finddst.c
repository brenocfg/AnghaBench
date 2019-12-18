#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct ip6_rthdr0 {struct in6_addr* ip6r0_addr; } ;
struct ip6_rthdr {int ip6r_len; int /*<<< orphan*/  ip6r_type; } ;
struct in6_addr {int dummy; } ;
struct ip6_hdr {int ip6_nxt; struct in6_addr ip6_dst; } ;
struct ip6_frag {int dummy; } ;
struct TYPE_3__ {int const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  IPPROTO_AH 138 
#define  IPPROTO_DSTOPTS 137 
#define  IPPROTO_ESP 136 
#define  IPPROTO_FRAGMENT 135 
#define  IPPROTO_HOPOPTS 134 
#define  IPPROTO_IPCOMP 133 
#define  IPPROTO_MOBILITY 132 
#define  IPPROTO_MOBILITY_OLD 131 
#define  IPPROTO_ROUTING 130 
#define  IPV6_RTHDR_TYPE_0 129 
#define  IPV6_RTHDR_TYPE_2 128 
 int /*<<< orphan*/  ND_TCHECK (struct ip6_rthdr const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  UNALIGNED_MEMCPY (struct in6_addr*,struct in6_addr const*,int) ; 

__attribute__((used)) static void
ip6_finddst(netdissect_options *ndo, struct in6_addr *dst,
            const struct ip6_hdr *ip6)
{
	const u_char *cp;
	int advance;
	u_int nh;
	const struct in6_addr *dst_addr;
	const struct ip6_rthdr *dp;
	const struct ip6_rthdr0 *dp0;
	const struct in6_addr *addr;
	int i, len;

	cp = (const u_char *)ip6;
	advance = sizeof(struct ip6_hdr);
	nh = ip6->ip6_nxt;
	dst_addr = &ip6->ip6_dst;

	while (cp < ndo->ndo_snapend) {
		cp += advance;

		switch (nh) {

		case IPPROTO_HOPOPTS:
		case IPPROTO_DSTOPTS:
		case IPPROTO_MOBILITY_OLD:
		case IPPROTO_MOBILITY:
			/*
			 * These have a header length byte, following
			 * the next header byte, giving the length of
			 * the header, in units of 8 octets, excluding
			 * the first 8 octets.
			 */
			ND_TCHECK2(*cp, 2);
			advance = (int)((*(cp + 1) + 1) << 3);
			nh = *cp;
			break;

		case IPPROTO_FRAGMENT:
			/*
			 * The byte following the next header byte is
			 * marked as reserved, and the header is always
			 * the same size.
			 */
			ND_TCHECK2(*cp, 1);
			advance = sizeof(struct ip6_frag);
			nh = *cp;
			break;

		case IPPROTO_ROUTING:
			/*
			 * OK, we found it.
			 */
			dp = (const struct ip6_rthdr *)cp;
			ND_TCHECK(*dp);
			len = dp->ip6r_len;
			switch (dp->ip6r_type) {

			case IPV6_RTHDR_TYPE_0:
			case IPV6_RTHDR_TYPE_2:		/* Mobile IPv6 ID-20 */
				dp0 = (const struct ip6_rthdr0 *)dp;
				if (len % 2 == 1)
					goto trunc;
				len >>= 1;
				addr = &dp0->ip6r0_addr[0];
				for (i = 0; i < len; i++) {
					if ((const u_char *)(addr + 1) > ndo->ndo_snapend)
						goto trunc;

					dst_addr = addr;
					addr++;
				}
				break;

			default:
				break;
			}

			/*
			 * Only one routing header to a customer.
			 */
			goto done;

		case IPPROTO_AH:
		case IPPROTO_ESP:
		case IPPROTO_IPCOMP:
		default:
			/*
			 * AH and ESP are, in the RFCs that describe them,
			 * described as being "viewed as an end-to-end
			 * payload" "in the IPv6 context, so that they
			 * "should appear after hop-by-hop, routing, and
			 * fragmentation extension headers".  We assume
			 * that's the case, and stop as soon as we see
			 * one.  (We can't handle an ESP header in
			 * the general case anyway, as its length depends
			 * on the encryption algorithm.)
			 *
			 * IPComp is also "viewed as an end-to-end
			 * payload" "in the IPv6 context".
			 *
			 * All other protocols are assumed to be the final
			 * protocol.
			 */
			goto done;
		}
	}

done:
trunc:
	UNALIGNED_MEMCPY(dst, dst_addr, sizeof(struct in6_addr));
}