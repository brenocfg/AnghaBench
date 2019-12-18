#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int type; int max_frame_size; } ;
struct TYPE_6__ {TYPE_1__ mac; } ;
struct adapter {TYPE_2__ hw; } ;
typedef  TYPE_3__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_7__ {int isc_max_frame_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETHER_CRC_LEN ; 
 int ETHER_HDR_LEN ; 
 int ETHER_MAX_LEN ; 
 int /*<<< orphan*/  IOCTL_DEBUGOUT (char*) ; 
 int MAX_JUMBO_FRAME_SIZE ; 
#define  e1000_80003es2lan 141 
#define  e1000_82542 140 
#define  e1000_82571 139 
#define  e1000_82572 138 
#define  e1000_82574 137 
#define  e1000_82583 136 
#define  e1000_ich10lan 135 
#define  e1000_ich8lan 134 
#define  e1000_ich9lan 133 
#define  e1000_pch2lan 132 
#define  e1000_pch_cnp 131 
#define  e1000_pch_lpt 130 
#define  e1000_pch_spt 129 
#define  e1000_pchlan 128 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_3__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 
 int igb_mac_min ; 

__attribute__((used)) static int
em_if_mtu_set(if_ctx_t ctx, uint32_t mtu)
{
	int max_frame_size;
	struct adapter *adapter = iflib_get_softc(ctx);
	if_softc_ctx_t scctx = iflib_get_softc_ctx(ctx);

	 IOCTL_DEBUGOUT("ioctl rcv'd: SIOCSIFMTU (Set Interface MTU)");

	switch (adapter->hw.mac.type) {
	case e1000_82571:
	case e1000_82572:
	case e1000_ich9lan:
	case e1000_ich10lan:
	case e1000_pch2lan:
	case e1000_pch_lpt:
	case e1000_pch_spt:
	case e1000_pch_cnp:
	case e1000_82574:
	case e1000_82583:
	case e1000_80003es2lan:
		/* 9K Jumbo Frame size */
		max_frame_size = 9234;
		break;
	case e1000_pchlan:
		max_frame_size = 4096;
		break;
	case e1000_82542:
	case e1000_ich8lan:
		/* Adapters that do not support jumbo frames */
		max_frame_size = ETHER_MAX_LEN;
		break;
	default:
		if (adapter->hw.mac.type >= igb_mac_min)
			max_frame_size = 9234;
		else /* lem */
			max_frame_size = MAX_JUMBO_FRAME_SIZE;
	}
	if (mtu > max_frame_size - ETHER_HDR_LEN - ETHER_CRC_LEN) {
		return (EINVAL);
	}

	scctx->isc_max_frame_size = adapter->hw.mac.max_frame_size =
	    mtu + ETHER_HDR_LEN + ETHER_CRC_LEN;
	return (0);
}