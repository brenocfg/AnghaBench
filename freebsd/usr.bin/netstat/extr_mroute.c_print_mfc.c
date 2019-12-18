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
typedef  int vifi_t ;
typedef  int /*<<< orphan*/  u_long ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct mfc {scalar_t__* mfc_ttls; struct bw_meter* mfc_bw_meter; int /*<<< orphan*/  mfc_parent; int /*<<< orphan*/  mfc_pkt_cnt; int /*<<< orphan*/  mfc_mcastgrp; int /*<<< orphan*/  mfc_origin; } ;
struct bw_meter {struct bw_meter* bm_mfc_next; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  bw_meter ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int kread (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numeric_addr ; 
 int /*<<< orphan*/  print_bw_meter (struct bw_meter*,int*) ; 
 int /*<<< orphan*/  routename (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

__attribute__((used)) static void
print_mfc(struct mfc *m, int maxvif, int *banner_printed)
{
	struct sockaddr_in sin;
	struct sockaddr *sa = (struct sockaddr *)&sin;
	struct bw_meter bw_meter, *bwm;
	int bw_banner_printed;
	int error;
	vifi_t vifi;

	bw_banner_printed = 0;
	memset(&sin, 0, sizeof(sin));
	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;

	if (! *banner_printed) {
		xo_open_list("multicast-forwarding-entry");
		xo_emit("\n{T:IPv4 Multicast Forwarding Table}\n"
		    " {T:Origin}          {T:Group}            "
		    " {T:Packets In-Vif}  {T:Out-Vifs:Ttls}\n");
		*banner_printed = 1;
	}

	memcpy(&sin.sin_addr, &m->mfc_origin, sizeof(sin.sin_addr));
	xo_emit(" {:origin-address/%-15.15s}", routename(sa, numeric_addr));
	memcpy(&sin.sin_addr, &m->mfc_mcastgrp, sizeof(sin.sin_addr));
	xo_emit(" {:group-address/%-15.15s}",
	    routename(sa, numeric_addr));
	xo_emit(" {:sent-packets/%9lu}", m->mfc_pkt_cnt);
	xo_emit("  {:parent/%3d}   ", m->mfc_parent);
	xo_open_list("vif-ttl");
	for (vifi = 0; vifi <= maxvif; vifi++) {
		if (m->mfc_ttls[vifi] > 0) {
			xo_open_instance("vif-ttl");
			xo_emit(" {k:vif/%u}:{:ttl/%u}", vifi,
			    m->mfc_ttls[vifi]);
			xo_close_instance("vif-ttl");
		}
	}
	xo_close_list("vif-ttl");
	xo_emit("\n");

	/*
	 * XXX We break the rules and try to use KVM to read the
	 * bandwidth meters, they are not retrievable via sysctl yet.
	 */
	bwm = m->mfc_bw_meter;
	while (bwm != NULL) {
		error = kread((u_long)bwm, (char *)&bw_meter,
		    sizeof(bw_meter));
		if (error)
			break;
		print_bw_meter(&bw_meter, &bw_banner_printed);
		bwm = bw_meter.bm_mfc_next;
	}
	if (banner_printed)
		xo_close_list("bandwidth-meter");
}