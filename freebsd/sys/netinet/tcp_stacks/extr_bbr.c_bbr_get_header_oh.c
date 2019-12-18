#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct tcphdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ rc_inc_enet_oh; scalar_t__ rc_inc_ip_oh; scalar_t__ rc_inc_tcp_oh; } ;
struct tcp_bbr {int rc_last_options; TYPE_1__ r_ctl; scalar_t__ r_is_v6; } ;
struct ip6_hdr {int dummy; } ;
struct ip {int dummy; } ;
struct ether_header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t
bbr_get_header_oh(struct tcp_bbr *bbr)
{
	int seg_oh;

	seg_oh = 0;
	if (bbr->r_ctl.rc_inc_tcp_oh) {
		/* Do we include TCP overhead? */
		seg_oh = (bbr->rc_last_options + sizeof(struct tcphdr));
	}
	if (bbr->r_ctl.rc_inc_ip_oh) {
		/* Do we include IP overhead? */
#ifdef INET6
		if (bbr->r_is_v6)
			seg_oh += sizeof(struct ip6_hdr);
		else
#endif
#ifdef INET
			seg_oh += sizeof(struct ip);
#endif
	}
	if (bbr->r_ctl.rc_inc_enet_oh) {
		/* Do we include the ethernet overhead?  */
		seg_oh += sizeof(struct ether_header);
	}
	return(seg_oh);
}