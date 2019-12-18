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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  drv_event_eapol_rx (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void wpa_driver_privsep_event_rx_eapol(void *ctx, u8 *buf, size_t len)
{
	if (len < ETH_ALEN)
		return;
	drv_event_eapol_rx(ctx, buf, buf + ETH_ALEN, len - ETH_ALEN);
}