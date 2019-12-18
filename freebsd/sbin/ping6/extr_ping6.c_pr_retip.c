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
struct ip6_rthdr {int ip6r_nxt; int /*<<< orphan*/  ip6r_len; } ;
struct ip6_hdr {int ip6_nxt; } ;
struct ip6_hbh {int ip6h_nxt; int /*<<< orphan*/  ip6h_len; } ;
struct ip6_frag {int ip6f_nxt; } ;
struct ip6_dest {int ip6d_nxt; int /*<<< orphan*/  ip6d_len; } ;
struct ah {int ah_nxt; int /*<<< orphan*/  ah_len; } ;
typedef  int /*<<< orphan*/  ah ;

/* Variables and functions */
#define  IPPROTO_AH 136 
#define  IPPROTO_DSTOPTS 135 
#define  IPPROTO_ESP 134 
#define  IPPROTO_FRAGMENT 133 
#define  IPPROTO_HOPOPTS 132 
#define  IPPROTO_ICMPV6 131 
#define  IPPROTO_ROUTING 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  memcpy (struct ah*,int*,int) ; 
 int /*<<< orphan*/  pr_iph (struct ip6_hdr*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
pr_retip(struct ip6_hdr *ip6, u_char *end)
{
	u_char *cp = (u_char *)ip6, nh;
	int hlen;

	if ((size_t)(end - (u_char *)ip6) < sizeof(*ip6)) {
		printf("IP6");
		goto trunc;
	}
	pr_iph(ip6);
	hlen = sizeof(*ip6);

	nh = ip6->ip6_nxt;
	cp += hlen;
	while (end - cp >= 8) {
		struct ah ah;

		switch (nh) {
		case IPPROTO_HOPOPTS:
			printf("HBH ");
			hlen = (((struct ip6_hbh *)cp)->ip6h_len+1) << 3;
			nh = ((struct ip6_hbh *)cp)->ip6h_nxt;
			break;
		case IPPROTO_DSTOPTS:
			printf("DSTOPT ");
			hlen = (((struct ip6_dest *)cp)->ip6d_len+1) << 3;
			nh = ((struct ip6_dest *)cp)->ip6d_nxt;
			break;
		case IPPROTO_FRAGMENT:
			printf("FRAG ");
			hlen = sizeof(struct ip6_frag);
			nh = ((struct ip6_frag *)cp)->ip6f_nxt;
			break;
		case IPPROTO_ROUTING:
			printf("RTHDR ");
			hlen = (((struct ip6_rthdr *)cp)->ip6r_len+1) << 3;
			nh = ((struct ip6_rthdr *)cp)->ip6r_nxt;
			break;
#ifdef IPSEC
		case IPPROTO_AH:
			printf("AH ");
			memcpy(&ah, cp, sizeof(ah));
			hlen = (ah.ah_len+2) << 2;
			nh = ah.ah_nxt;
			break;
#endif
		case IPPROTO_ICMPV6:
			printf("ICMP6: type = %d, code = %d\n",
			    *cp, *(cp + 1));
			return;
		case IPPROTO_ESP:
			printf("ESP\n");
			return;
		case IPPROTO_TCP:
			printf("TCP: from port %u, to port %u (decimal)\n",
			    (*cp * 256 + *(cp + 1)),
			    (*(cp + 2) * 256 + *(cp + 3)));
			return;
		case IPPROTO_UDP:
			printf("UDP: from port %u, to port %u (decimal)\n",
			    (*cp * 256 + *(cp + 1)),
			    (*(cp + 2) * 256 + *(cp + 3)));
			return;
		default:
			printf("Unknown Header(%d)\n", nh);
			return;
		}

		if ((cp += hlen) >= end)
			goto trunc;
	}
	if (end - cp < 8)
		goto trunc;

	putchar('\n');
	return;

  trunc:
	printf("...\n");
	return;
}