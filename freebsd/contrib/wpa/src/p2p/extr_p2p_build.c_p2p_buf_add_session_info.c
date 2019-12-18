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
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  P2P_ATTR_SESSION_INFORMATION_DATA ; 
 size_t os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

void p2p_buf_add_session_info(struct wpabuf *buf, const char *info)
{
	size_t info_len = 0;

	if (info && info[0])
		info_len = os_strlen(info);

	/* Session Information Data Info */
	wpabuf_put_u8(buf, P2P_ATTR_SESSION_INFORMATION_DATA);
	wpabuf_put_le16(buf, (u16) info_len);

	if (info) {
		wpabuf_put_data(buf, info, info_len);
		wpa_printf(MSG_DEBUG, "P2P: * Session Info Data (%s)", info);
	}
}