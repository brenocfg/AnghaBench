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
typedef  int /*<<< orphan*/  u_char ;
struct udphdr {int uh_dport; } ;
struct ip6_hdr {int ip6_nxt; } ;
struct ip6_hbh {int ip6h_len; int ip6h_nxt; } ;
struct ip6_frag {int ip6f_offlg; int ip6f_nxt; } ;
struct ah {int ah_len; int ah_nxt; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int*) ; 
 int IP6F_OFF_MASK ; 
#define  IPPROTO_AH 134 
#define  IPPROTO_DSTOPTS 133 
#define  IPPROTO_FRAGMENT 132 
#define  IPPROTO_HOPOPTS 131 
#define  IPPROTO_ROUTING 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 scalar_t__ ND_TTEST (int) ; 

__attribute__((used)) static const struct udphdr *
get_upperlayer(netdissect_options *ndo, const u_char *bp, u_int *prot)
{
	const u_char *ep;
	const struct ip6_hdr *ip6 = (const struct ip6_hdr *)bp;
	const struct udphdr *uh;
	const struct ip6_hbh *hbh;
	const struct ip6_frag *fragh;
	const struct ah *ah;
	u_int nh;
	int hlen;

	/* 'ep' points to the end of available data. */
	ep = ndo->ndo_snapend;

	if (!ND_TTEST(ip6->ip6_nxt))
		return NULL;

	nh = ip6->ip6_nxt;
	hlen = sizeof(struct ip6_hdr);

	while (bp < ep) {
		bp += hlen;

		switch(nh) {
		case IPPROTO_UDP:
		case IPPROTO_TCP:
			uh = (const struct udphdr *)bp;
			if (ND_TTEST(uh->uh_dport)) {
				*prot = nh;
				return(uh);
			}
			else
				return(NULL);
			/* NOTREACHED */

		case IPPROTO_HOPOPTS:
		case IPPROTO_DSTOPTS:
		case IPPROTO_ROUTING:
			hbh = (const struct ip6_hbh *)bp;
			if (!ND_TTEST(hbh->ip6h_len))
				return(NULL);
			nh = hbh->ip6h_nxt;
			hlen = (hbh->ip6h_len + 1) << 3;
			break;

		case IPPROTO_FRAGMENT: /* this should be odd, but try anyway */
			fragh = (const struct ip6_frag *)bp;
			if (!ND_TTEST(fragh->ip6f_offlg))
				return(NULL);
			/* fragments with non-zero offset are meaningless */
			if ((EXTRACT_16BITS(&fragh->ip6f_offlg) & IP6F_OFF_MASK) != 0)
				return(NULL);
			nh = fragh->ip6f_nxt;
			hlen = sizeof(struct ip6_frag);
			break;

		case IPPROTO_AH:
			ah = (const struct ah *)bp;
			if (!ND_TTEST(ah->ah_len))
				return(NULL);
			nh = ah->ah_nxt;
			hlen = (ah->ah_len + 2) << 2;
			break;

		default:	/* unknown or undecodable header */
			*prot = nh; /* meaningless, but set here anyway */
			return(NULL);
		}
	}

	return(NULL);		/* should be notreached, though */
}