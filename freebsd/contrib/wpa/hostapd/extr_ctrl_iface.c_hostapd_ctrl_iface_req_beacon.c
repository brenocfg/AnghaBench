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
struct wpabuf {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int hex2byte (char const*) ; 
 int hostapd_send_beacon_req (struct hostapd_data*,int*,int,struct wpabuf*) ; 
 scalar_t__ hwaddr_aton (char const*,int*) ; 
 int os_snprintf (char*,size_t,char*,int) ; 
 char* os_strchr (char const*,char) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 struct wpabuf* wpabuf_parse_bin (char const*) ; 

__attribute__((used)) static int hostapd_ctrl_iface_req_beacon(struct hostapd_data *hapd,
					 const char *cmd, char *reply,
					 size_t reply_size)
{
	u8 addr[ETH_ALEN];
	const char *pos;
	struct wpabuf *req;
	int ret;
	u8 req_mode = 0;

	if (hwaddr_aton(cmd, addr))
		return -1;
	pos = os_strchr(cmd, ' ');
	if (!pos)
		return -1;
	pos++;
	if (os_strncmp(pos, "req_mode=", 9) == 0) {
		int val = hex2byte(pos + 9);

		if (val < 0)
			return -1;
		req_mode = val;
		pos += 11;
		pos = os_strchr(pos, ' ');
		if (!pos)
			return -1;
		pos++;
	}
	req = wpabuf_parse_bin(pos);
	if (!req)
		return -1;

	ret = hostapd_send_beacon_req(hapd, addr, req_mode, req);
	wpabuf_free(req);
	if (ret >= 0)
		ret = os_snprintf(reply, reply_size, "%d", ret);
	return ret;
}