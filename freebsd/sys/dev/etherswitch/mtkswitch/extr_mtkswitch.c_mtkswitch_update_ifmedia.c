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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  IFM_1000_T ; 
 int /*<<< orphan*/  IFM_100_TX ; 
 int /*<<< orphan*/  IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_ETH_RXPAUSE ; 
 int /*<<< orphan*/  IFM_ETH_TXPAUSE ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_HDX ; 
 int /*<<< orphan*/  IFM_NONE ; 
 int MTKSWITCH_DUPLEX ; 
 int MTKSWITCH_LINK_UP ; 
 int MTKSWITCH_RXFLOW ; 
#define  MTKSWITCH_SPEED_10 130 
#define  MTKSWITCH_SPEED_100 129 
#define  MTKSWITCH_SPEED_1000 128 
 int MTKSWITCH_SPEED_MASK ; 
 int MTKSWITCH_TXFLOW ; 

__attribute__((used)) static void
mtkswitch_update_ifmedia(uint32_t portstatus, u_int *media_status,
    u_int *media_active)
{
	*media_active = IFM_ETHER;
	*media_status = IFM_AVALID;

	if ((portstatus & MTKSWITCH_LINK_UP) != 0)
		*media_status |= IFM_ACTIVE;
	else {
		*media_active |= IFM_NONE;
		return;
	}

	switch (portstatus & MTKSWITCH_SPEED_MASK) {
	case MTKSWITCH_SPEED_10:
		*media_active |= IFM_10_T;
		break;
	case MTKSWITCH_SPEED_100:
		*media_active |= IFM_100_TX;
		break;
	case MTKSWITCH_SPEED_1000:
		*media_active |= IFM_1000_T;
		break;
	}

	if ((portstatus & MTKSWITCH_DUPLEX) != 0)
		*media_active |= IFM_FDX;
	else
		*media_active |= IFM_HDX;

	if ((portstatus & MTKSWITCH_TXFLOW) != 0)
		*media_active |= IFM_ETH_TXPAUSE;
	if ((portstatus & MTKSWITCH_RXFLOW) != 0)
		*media_active |= IFM_ETH_RXPAUSE;
}