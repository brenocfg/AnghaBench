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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_int ;
struct udphdr {int dummy; } ;
struct ip6_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int nextproto6_cksum (int /*<<< orphan*/ *,struct ip6_hdr const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udp6_cksum(netdissect_options *ndo, const struct ip6_hdr *ip6,
		      const struct udphdr *up, u_int len)
{
	return nextproto6_cksum(ndo, ip6, (const uint8_t *)(const void *)up, len, len,
				IPPROTO_UDP);
}