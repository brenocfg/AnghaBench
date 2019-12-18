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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  OUI_QCA ; 
 int QCA_VENDOR_ELEM_P2P_PREF_CHAN_LIST ; 
 int WLAN_EID_VENDOR_SPECIFIC ; 
 scalar_t__ p2p_freq_to_channel (int /*<<< orphan*/  const,int*,int*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  wpabuf_put_be24 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

void p2p_buf_add_pref_channel_list(struct wpabuf *buf,
				   const u32 *preferred_freq_list,
				   unsigned int size)
{
	unsigned int i, count = 0;
	u8 op_class, op_channel;

	if (!size)
		return;

	/*
	 * First, determine the number of P2P supported channels in the
	 * pref_freq_list returned from driver. This is needed for calculations
	 * of the vendor IE size.
	 */
	for (i = 0; i < size; i++) {
		if (p2p_freq_to_channel(preferred_freq_list[i], &op_class,
					&op_channel) == 0)
			count++;
	}

	wpabuf_put_u8(buf, WLAN_EID_VENDOR_SPECIFIC);
	wpabuf_put_u8(buf, 4 + count * sizeof(u16));
	wpabuf_put_be24(buf, OUI_QCA);
	wpabuf_put_u8(buf, QCA_VENDOR_ELEM_P2P_PREF_CHAN_LIST);
	for (i = 0; i < size; i++) {
		if (p2p_freq_to_channel(preferred_freq_list[i], &op_class,
					&op_channel) < 0) {
			wpa_printf(MSG_DEBUG, "Unsupported frequency %u MHz",
				   preferred_freq_list[i]);
			continue;
		}
		wpabuf_put_u8(buf, op_class);
		wpabuf_put_u8(buf, op_channel);
	}
}