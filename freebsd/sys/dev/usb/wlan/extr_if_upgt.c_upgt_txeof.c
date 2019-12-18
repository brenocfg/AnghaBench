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
struct usb_xfer {int dummy; } ;
struct upgt_data {int /*<<< orphan*/ * ni; int /*<<< orphan*/ * m; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_tx_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
upgt_txeof(struct usb_xfer *xfer, struct upgt_data *data)
{

	if (data->m) {
		/* XXX status? */
		ieee80211_tx_complete(data->ni, data->m, 0);
		data->m = NULL;
		data->ni = NULL;
	}
}