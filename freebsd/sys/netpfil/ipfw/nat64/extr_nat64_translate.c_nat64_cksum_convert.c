#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ip6_hdr {int /*<<< orphan*/  ip6_src; } ;
struct TYPE_3__ {int s_addr; } ;
struct TYPE_4__ {int s_addr; } ;
struct ip {TYPE_1__ ip_dst; TYPE_2__ ip_src; } ;

/* Variables and functions */

__attribute__((used)) static uint16_t
nat64_cksum_convert(struct ip6_hdr *ip6, struct ip *ip)
{
	uint32_t sum;
	uint16_t *p;

	sum = ~ip->ip_src.s_addr >> 16;
	sum += ~ip->ip_src.s_addr & 0xffff;
	sum += ~ip->ip_dst.s_addr >> 16;
	sum += ~ip->ip_dst.s_addr & 0xffff;

	for (p = (uint16_t *)&ip6->ip6_src;
	    p < (uint16_t *)(&ip6->ip6_src + 2); p++)
		sum += *p;

	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);
	return (sum);
}