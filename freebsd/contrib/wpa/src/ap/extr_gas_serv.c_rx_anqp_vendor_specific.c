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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct hostapd_data {int dummy; } ;
struct anqp_query_info {int dummy; } ;

/* Variables and functions */
#define  HS20_ANQP_OUI_TYPE 130 
#define  MBO_ANQP_OUI_TYPE 129 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ OUI_WFA ; 
#define  P2P_OUI_TYPE 128 
 scalar_t__ WPA_GET_BE24 (int const*) ; 
 int /*<<< orphan*/  rx_anqp_vendor_specific_hs20 (struct hostapd_data*,int const*,int const*,struct anqp_query_info*) ; 
 int /*<<< orphan*/  rx_anqp_vendor_specific_mbo (struct hostapd_data*,int const*,int const*,struct anqp_query_info*) ; 
 int /*<<< orphan*/  rx_anqp_vendor_specific_p2p (struct hostapd_data*,struct anqp_query_info*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void rx_anqp_vendor_specific(struct hostapd_data *hapd,
				    const u8 *pos, const u8 *end,
				    struct anqp_query_info *qi)
{
	u32 oui;

	if (end - pos < 4) {
		wpa_printf(MSG_DEBUG, "ANQP: Too short vendor specific ANQP "
			   "Query element");
		return;
	}

	oui = WPA_GET_BE24(pos);
	pos += 3;
	if (oui != OUI_WFA) {
		wpa_printf(MSG_DEBUG, "ANQP: Unsupported vendor OUI %06x",
			   oui);
		return;
	}

	switch (*pos) {
#ifdef CONFIG_P2P
	case P2P_OUI_TYPE:
		rx_anqp_vendor_specific_p2p(hapd, qi);
		break;
#endif /* CONFIG_P2P */
#ifdef CONFIG_HS20
	case HS20_ANQP_OUI_TYPE:
		rx_anqp_vendor_specific_hs20(hapd, pos + 1, end, qi);
		break;
#endif /* CONFIG_HS20 */
#ifdef CONFIG_MBO
	case MBO_ANQP_OUI_TYPE:
		rx_anqp_vendor_specific_mbo(hapd, pos + 1, end, qi);
		break;
#endif /* CONFIG_MBO */
	default:
		wpa_printf(MSG_DEBUG, "ANQP: Unsupported WFA vendor type %u",
			   *pos);
		break;
	}
}