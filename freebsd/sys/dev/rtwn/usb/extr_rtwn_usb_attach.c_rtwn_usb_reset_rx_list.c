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
struct rtwn_usb_softc {scalar_t__ uc_rx_off; scalar_t__ uc_rx_stat_len; struct rtwn_data* uc_rx; } ;
struct rtwn_data {int /*<<< orphan*/ * m; } ;

/* Variables and functions */
 int RTWN_USB_RX_LIST_COUNT ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtwn_usb_reset_rx_list(struct rtwn_usb_softc *uc)
{
	int i;

	for (i = 0; i < RTWN_USB_RX_LIST_COUNT; i++) {
		struct rtwn_data *dp = &uc->uc_rx[i];

		if (dp->m != NULL) {
			m_freem(dp->m);
			dp->m = NULL;
		}
	}
	uc->uc_rx_stat_len = 0;
	uc->uc_rx_off = 0;
}