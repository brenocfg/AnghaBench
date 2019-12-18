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
struct bwn_pio {int /*<<< orphan*/ * wme; int /*<<< orphan*/  mcast; } ;
struct TYPE_2__ {struct bwn_pio pio; } ;
struct bwn_mac {int mac_flags; TYPE_1__ mac_method; } ;

/* Variables and functions */
 int BWN_MAC_FLAG_DMA ; 
 size_t WME_AC_BE ; 
 size_t WME_AC_BK ; 
 size_t WME_AC_VI ; 
 size_t WME_AC_VO ; 
 int /*<<< orphan*/  bwn_destroy_queue_tx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bwn_pio_stop(struct bwn_mac *mac)
{
	struct bwn_pio *pio;

	if (mac->mac_flags & BWN_MAC_FLAG_DMA)
		return;
	pio = &mac->mac_method.pio;

	bwn_destroy_queue_tx(&pio->mcast);
	bwn_destroy_queue_tx(&pio->wme[WME_AC_VO]);
	bwn_destroy_queue_tx(&pio->wme[WME_AC_VI]);
	bwn_destroy_queue_tx(&pio->wme[WME_AC_BE]);
	bwn_destroy_queue_tx(&pio->wme[WME_AC_BK]);
}