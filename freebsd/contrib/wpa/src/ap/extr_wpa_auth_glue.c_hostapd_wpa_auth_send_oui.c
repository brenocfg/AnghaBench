#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_auth_oui_iface_iter_data {size_t data_len; int /*<<< orphan*/  oui_suffix; int /*<<< orphan*/  const* data; int /*<<< orphan*/  const* dst_addr; struct hostapd_data* src_hapd; } ;
struct hostapd_data {int /*<<< orphan*/  own_addr; TYPE_1__* iface; } ;
struct eth_p_oui_ctx {int dummy; } ;
struct TYPE_4__ {int (* for_each_interface ) (TYPE_2__*,int /*<<< orphan*/ ,struct wpa_auth_oui_iface_iter_data*) ;} ;
struct TYPE_3__ {TYPE_2__* interfaces; } ;

/* Variables and functions */
 int eth_p_oui_send (struct eth_p_oui_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  hostapd_wpa_auth_oui_iter ; 
 struct eth_p_oui_ctx* hostapd_wpa_get_oui (struct hostapd_data*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,struct wpa_auth_oui_iface_iter_data*) ; 

__attribute__((used)) static int hostapd_wpa_auth_send_oui(void *ctx, const u8 *dst, u8 oui_suffix,
				     const u8 *data, size_t data_len)
{
#ifdef CONFIG_ETH_P_OUI
	struct hostapd_data *hapd = ctx;
	struct eth_p_oui_ctx *oui_ctx;

#ifdef CONFIG_IEEE80211R_AP
	if (hapd->iface->interfaces &&
	    hapd->iface->interfaces->for_each_interface) {
		struct wpa_auth_oui_iface_iter_data idata;
		int res;

		idata.src_hapd = hapd;
		idata.dst_addr = dst;
		idata.data = data;
		idata.data_len = data_len;
		idata.oui_suffix = oui_suffix;
		res = hapd->iface->interfaces->for_each_interface(
			hapd->iface->interfaces, hostapd_wpa_auth_oui_iter,
			&idata);
		if (res == 1)
			return data_len;
	}
#endif /* CONFIG_IEEE80211R_AP */

	oui_ctx = hostapd_wpa_get_oui(hapd, oui_suffix);
	if (!oui_ctx)
		return -1;

	return eth_p_oui_send(oui_ctx, hapd->own_addr, dst, data, data_len);
#else /* CONFIG_ETH_P_OUI */
	return -1;
#endif /* CONFIG_ETH_P_OUI */
}