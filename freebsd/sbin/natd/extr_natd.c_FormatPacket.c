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
struct udphdr {int /*<<< orphan*/  uh_dport; int /*<<< orphan*/  uh_sport; } ;
struct tcphdr {int /*<<< orphan*/  th_dport; int /*<<< orphan*/  th_sport; } ;
struct ip {int ip_p; int ip_hl; int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
struct icmp {int icmp_type; int icmp_code; } ;

/* Variables and functions */
#define  IPPROTO_ICMP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char* FormatPacket (struct ip* ip)
{
	static char	buf[256];
	struct tcphdr*	tcphdr;
	struct udphdr*	udphdr;
	struct icmp*	icmphdr;
	char		src[20];
	char		dst[20];

	strcpy (src, inet_ntoa (ip->ip_src));
	strcpy (dst, inet_ntoa (ip->ip_dst));

	switch (ip->ip_p) {
	case IPPROTO_TCP:
		tcphdr = (struct tcphdr*) ((char*) ip + (ip->ip_hl << 2));
		sprintf (buf, "[TCP] %s:%d -> %s:%d",
			      src,
			      ntohs (tcphdr->th_sport),
			      dst,
			      ntohs (tcphdr->th_dport));
		break;

	case IPPROTO_UDP:
		udphdr = (struct udphdr*) ((char*) ip + (ip->ip_hl << 2));
		sprintf (buf, "[UDP] %s:%d -> %s:%d",
			      src,
			      ntohs (udphdr->uh_sport),
			      dst,
			      ntohs (udphdr->uh_dport));
		break;

	case IPPROTO_ICMP:
		icmphdr = (struct icmp*) ((char*) ip + (ip->ip_hl << 2));
		sprintf (buf, "[ICMP] %s -> %s %u(%u)",
			      src,
			      dst,
			      icmphdr->icmp_type,
			      icmphdr->icmp_code);
		break;

	default:
		sprintf (buf, "[%d] %s -> %s ", ip->ip_p, src, dst);
		break;
	}

	return buf;
}