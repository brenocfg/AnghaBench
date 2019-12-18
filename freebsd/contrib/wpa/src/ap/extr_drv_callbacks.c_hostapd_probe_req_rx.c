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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_data {size_t num_probereq_cb; TYPE_1__* probereq_cb; } ;
struct TYPE_2__ {scalar_t__ (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  random_add_randomness (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int) ; 

int hostapd_probe_req_rx(struct hostapd_data *hapd, const u8 *sa, const u8 *da,
			 const u8 *bssid, const u8 *ie, size_t ie_len,
			 int ssi_signal)
{
	size_t i;
	int ret = 0;

	if (sa == NULL || ie == NULL)
		return -1;

	random_add_randomness(sa, ETH_ALEN);
	for (i = 0; hapd->probereq_cb && i < hapd->num_probereq_cb; i++) {
		if (hapd->probereq_cb[i].cb(hapd->probereq_cb[i].ctx,
					    sa, da, bssid, ie, ie_len,
					    ssi_signal) > 0) {
			ret = 1;
			break;
		}
	}
	return ret;
}