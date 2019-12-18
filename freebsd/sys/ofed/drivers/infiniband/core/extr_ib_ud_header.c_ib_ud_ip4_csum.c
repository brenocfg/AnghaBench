#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct ip {int ip_hl; int ip_v; TYPE_2__ ip_dst; TYPE_1__ ip_src; scalar_t__ ip_sum; int /*<<< orphan*/  ip_p; int /*<<< orphan*/  ip_ttl; int /*<<< orphan*/  ip_off; int /*<<< orphan*/  ip_id; int /*<<< orphan*/  ip_len; int /*<<< orphan*/  ip_tos; } ;
struct TYPE_6__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ttl; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  id; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  tos; } ;
struct ib_ud_header {TYPE_3__ ip4; } ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
 int /*<<< orphan*/  in_cksum_hdr (struct ip*) ; 

__sum16 ib_ud_ip4_csum(struct ib_ud_header *header)
{
#if defined(INET) || defined(INET6)
	struct ip iph;

	iph.ip_hl	= 5;
	iph.ip_v	= 4;
	iph.ip_tos	= header->ip4.tos;
	iph.ip_len	= header->ip4.tot_len;
	iph.ip_id	= header->ip4.id;
	iph.ip_off	= header->ip4.frag_off;
	iph.ip_ttl	= header->ip4.ttl;
	iph.ip_p	= header->ip4.protocol;
	iph.ip_sum	= 0;
	iph.ip_src.s_addr = header->ip4.saddr;
	iph.ip_dst.s_addr = header->ip4.daddr;

	return in_cksum_hdr(&iph);
#else
	return 0;
#endif
}