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
 int RTL8366_PLSR_FULLDUPLEX ; 
 int RTL8366_PLSR_LINK ; 
 int RTL8366_PLSR_RXPAUSE ; 
#define  RTL8366_PLSR_SPEED_10 130 
#define  RTL8366_PLSR_SPEED_100 129 
#define  RTL8366_PLSR_SPEED_1000 128 
 int RTL8366_PLSR_SPEED_MASK ; 
 int RTL8366_PLSR_TXPAUSE ; 

__attribute__((used)) static void
rtl8366rb_update_ifmedia(int portstatus, u_int *media_status, u_int *media_active)
{
	*media_active = IFM_ETHER;
	*media_status = IFM_AVALID;
	if ((portstatus & RTL8366_PLSR_LINK) != 0)
		*media_status |= IFM_ACTIVE;
	else {
		*media_active |= IFM_NONE;
		return;
	}
	switch (portstatus & RTL8366_PLSR_SPEED_MASK) {
	case RTL8366_PLSR_SPEED_10:
		*media_active |= IFM_10_T;
		break;
	case RTL8366_PLSR_SPEED_100:
		*media_active |= IFM_100_TX;
		break;
	case RTL8366_PLSR_SPEED_1000:
		*media_active |= IFM_1000_T;
		break;
	}
	if ((portstatus & RTL8366_PLSR_FULLDUPLEX) != 0)
		*media_active |= IFM_FDX;
	else
		*media_active |= IFM_HDX;
	if ((portstatus & RTL8366_PLSR_TXPAUSE) != 0)
		*media_active |= IFM_ETH_TXPAUSE;
	if ((portstatus & RTL8366_PLSR_RXPAUSE) != 0)
		*media_active |= IFM_ETH_RXPAUSE;
}