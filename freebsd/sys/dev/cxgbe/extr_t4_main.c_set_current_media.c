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
typedef  int u_int ;
struct link_config {scalar_t__ requested_aneg; int supported; int requested_fc; int requested_speed; } ;
struct ifmedia {TYPE_1__* ifm_cur; } ;
struct port_info {struct link_config link_cfg; struct ifmedia media; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 int FW_PORT_CAP32_ANEG ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int IFM_FDX ; 
 scalar_t__ IFM_NONE ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int /*<<< orphan*/  PORT_LOCK_ASSERT_OWNED (struct port_info*) ; 
 int /*<<< orphan*/  ifmedia_set (struct ifmedia*,int) ; 
 int port_mword (struct port_info*,int /*<<< orphan*/ ) ; 
 int port_top_speed (struct port_info*) ; 
 int /*<<< orphan*/  speed_to_fwcap (int) ; 

__attribute__((used)) static void
set_current_media(struct port_info *pi)
{
	struct link_config *lc;
	struct ifmedia *ifm;
	int mword;
	u_int speed;

	PORT_LOCK_ASSERT_OWNED(pi);

	/* Leave current media alone if it's already set to IFM_NONE. */
	ifm = &pi->media;
	if (ifm->ifm_cur != NULL &&
	    IFM_SUBTYPE(ifm->ifm_cur->ifm_media) == IFM_NONE)
		return;

	lc = &pi->link_cfg;
	if (lc->requested_aneg != AUTONEG_DISABLE &&
	    lc->supported & FW_PORT_CAP32_ANEG) {
		ifmedia_set(ifm, IFM_ETHER | IFM_AUTO);
		return;
	}
	mword = IFM_ETHER | IFM_FDX;
	if (lc->requested_fc & PAUSE_TX)
		mword |= IFM_ETH_TXPAUSE;
	if (lc->requested_fc & PAUSE_RX)
		mword |= IFM_ETH_RXPAUSE;
	if (lc->requested_speed == 0)
		speed = port_top_speed(pi) * 1000;	/* Gbps -> Mbps */
	else
		speed = lc->requested_speed;
	mword |= port_mword(pi, speed_to_fwcap(speed));
	ifmedia_set(ifm, mword);
}