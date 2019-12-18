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
struct sta_info {scalar_t__ hs20_deauth_requested; scalar_t__ remediation; } ;
struct radius_msg {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_ATTR_VENDOR_SPECIFIC ; 
#define  RADIUS_VENDOR_ATTR_WFA_HS20_DEAUTH_REQ 132 
#define  RADIUS_VENDOR_ATTR_WFA_HS20_SESSION_INFO_URL 131 
#define  RADIUS_VENDOR_ATTR_WFA_HS20_SUBSCR_REMEDIATION 130 
#define  RADIUS_VENDOR_ATTR_WFA_HS20_T_C_FILTERING 129 
#define  RADIUS_VENDOR_ATTR_WFA_HS20_T_C_URL 128 
 scalar_t__ RADIUS_VENDOR_ID_WFA ; 
 scalar_t__ WPA_GET_BE32 (int*) ; 
 int /*<<< orphan*/  ieee802_1x_hs20_deauth_req (struct hostapd_data*,struct sta_info*,int*,int) ; 
 int /*<<< orphan*/  ieee802_1x_hs20_session_info (struct hostapd_data*,struct sta_info*,int*,int,int) ; 
 int /*<<< orphan*/  ieee802_1x_hs20_sub_rem (struct sta_info*,int*,int) ; 
 int /*<<< orphan*/  ieee802_1x_hs20_t_c_filtering (struct hostapd_data*,struct sta_info*,int*,int) ; 
 int /*<<< orphan*/  ieee802_1x_hs20_t_c_url (struct hostapd_data*,struct sta_info*,int*,int) ; 
 scalar_t__ radius_msg_get_attr_ptr (struct radius_msg*,int /*<<< orphan*/ ,int**,size_t*,int*) ; 

__attribute__((used)) static void ieee802_1x_check_hs20(struct hostapd_data *hapd,
				  struct sta_info *sta,
				  struct radius_msg *msg,
				  int session_timeout)
{
#ifdef CONFIG_HS20
	u8 *buf, *pos, *end, type, sublen;
	size_t len;

	buf = NULL;
	sta->remediation = 0;
	sta->hs20_deauth_requested = 0;

	for (;;) {
		if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_VENDOR_SPECIFIC,
					    &buf, &len, buf) < 0)
			break;
		if (len < 6)
			continue;
		pos = buf;
		end = buf + len;
		if (WPA_GET_BE32(pos) != RADIUS_VENDOR_ID_WFA)
			continue;
		pos += 4;

		type = *pos++;
		sublen = *pos++;
		if (sublen < 2)
			continue; /* invalid length */
		sublen -= 2; /* skip header */
		if (pos + sublen > end)
			continue; /* invalid WFA VSA */

		switch (type) {
		case RADIUS_VENDOR_ATTR_WFA_HS20_SUBSCR_REMEDIATION:
			ieee802_1x_hs20_sub_rem(sta, pos, sublen);
			break;
		case RADIUS_VENDOR_ATTR_WFA_HS20_DEAUTH_REQ:
			ieee802_1x_hs20_deauth_req(hapd, sta, pos, sublen);
			break;
		case RADIUS_VENDOR_ATTR_WFA_HS20_SESSION_INFO_URL:
			ieee802_1x_hs20_session_info(hapd, sta, pos, sublen,
						     session_timeout);
			break;
		case RADIUS_VENDOR_ATTR_WFA_HS20_T_C_FILTERING:
			ieee802_1x_hs20_t_c_filtering(hapd, sta, pos, sublen);
			break;
		case RADIUS_VENDOR_ATTR_WFA_HS20_T_C_URL:
			ieee802_1x_hs20_t_c_url(hapd, sta, pos, sublen);
			break;
		}
	}
#endif /* CONFIG_HS20 */
}