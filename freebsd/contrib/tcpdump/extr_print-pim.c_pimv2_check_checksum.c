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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ip6_hdr {int dummy; } ;
struct ip {int dummy; } ;
struct cksum_vec {scalar_t__ len; int /*<<< orphan*/  const* ptr; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  enum checksum_status { ____Placeholder_checksum_status } checksum_status ;

/* Variables and functions */
 int CORRECT ; 
 int INCORRECT ; 
 int /*<<< orphan*/  IPPROTO_PIM ; 
 int IP_V (struct ip const*) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,scalar_t__) ; 
 int UNVERIFIED ; 
 scalar_t__ in_cksum (struct cksum_vec*,int) ; 
 scalar_t__ nextproto6_cksum (int /*<<< orphan*/ *,struct ip6_hdr const*,int /*<<< orphan*/  const*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum checksum_status
pimv2_check_checksum(netdissect_options *ndo, const u_char *bp,
		     const u_char *bp2, u_int len)
{
	const struct ip *ip;
	u_int cksum;

	if (!ND_TTEST2(bp[0], len)) {
		/* We don't have all the data. */
		return (UNVERIFIED);
	}
	ip = (const struct ip *)bp2;
	if (IP_V(ip) == 4) {
		struct cksum_vec vec[1];

		vec[0].ptr = bp;
		vec[0].len = len;
		cksum = in_cksum(vec, 1);
		return (cksum ? INCORRECT : CORRECT);
	} else if (IP_V(ip) == 6) {
		const struct ip6_hdr *ip6;

		ip6 = (const struct ip6_hdr *)bp2;
		cksum = nextproto6_cksum(ndo, ip6, bp, len, len, IPPROTO_PIM);
		return (cksum ? INCORRECT : CORRECT);
	} else {
		return (UNVERIFIED);
	}
}