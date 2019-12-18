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
struct p2p_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_IE_VENDOR_TYPE ; 
#define  WLAN_PA_GAS_COMEBACK_REQ 132 
#define  WLAN_PA_GAS_COMEBACK_RESP 131 
#define  WLAN_PA_GAS_INITIAL_REQ 130 
#define  WLAN_PA_GAS_INITIAL_RESP 129 
#define  WLAN_PA_VENDOR_SPECIFIC 128 
 int /*<<< orphan*/  WPA_GET_BE32 (int const*) ; 
 int /*<<< orphan*/  p2p_rx_gas_comeback_req (struct p2p_data*,int const*,int const*,size_t,int) ; 
 int /*<<< orphan*/  p2p_rx_gas_comeback_resp (struct p2p_data*,int const*,int const*,size_t,int) ; 
 int /*<<< orphan*/  p2p_rx_gas_initial_req (struct p2p_data*,int const*,int const*,size_t,int) ; 
 int /*<<< orphan*/  p2p_rx_gas_initial_resp (struct p2p_data*,int const*,int const*,size_t,int) ; 
 int /*<<< orphan*/  p2p_rx_p2p_action (struct p2p_data*,int const*,int const*,size_t,int) ; 

__attribute__((used)) static void p2p_rx_action_public(struct p2p_data *p2p, const u8 *da,
				 const u8 *sa, const u8 *bssid, const u8 *data,
				 size_t len, int freq)
{
	if (len < 1)
		return;

	switch (data[0]) {
	case WLAN_PA_VENDOR_SPECIFIC:
		data++;
		len--;
		if (len < 4)
			return;
		if (WPA_GET_BE32(data) != P2P_IE_VENDOR_TYPE)
			return;

		data += 4;
		len -= 4;

		p2p_rx_p2p_action(p2p, sa, data, len, freq);
		break;
	case WLAN_PA_GAS_INITIAL_REQ:
		p2p_rx_gas_initial_req(p2p, sa, data + 1, len - 1, freq);
		break;
	case WLAN_PA_GAS_INITIAL_RESP:
		p2p_rx_gas_initial_resp(p2p, sa, data + 1, len - 1, freq);
		break;
	case WLAN_PA_GAS_COMEBACK_REQ:
		p2p_rx_gas_comeback_req(p2p, sa, data + 1, len - 1, freq);
		break;
	case WLAN_PA_GAS_COMEBACK_RESP:
		p2p_rx_gas_comeback_resp(p2p, sa, data + 1, len - 1, freq);
		break;
	}
}