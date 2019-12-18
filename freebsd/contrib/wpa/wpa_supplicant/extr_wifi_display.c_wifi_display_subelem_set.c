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
struct wpabuf {int dummy; } ;
struct wpa_global {struct wpabuf** wfd_subelem; } ;

/* Variables and functions */
 int MAX_WFD_SUBELEMS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int atoi (char*) ; 
 scalar_t__ hexstr2bin (char*,int /*<<< orphan*/ ,size_t) ; 
 char* os_strchr (char*,char) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 size_t os_strlen (char*) ; 
 int wifi_display_subelem_set_from_ies (struct wpa_global*,struct wpabuf*) ; 
 int /*<<< orphan*/  wifi_display_update_wfd_ie (struct wpa_global*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

int wifi_display_subelem_set(struct wpa_global *global, char *cmd)
{
	char *pos;
	int subelem;
	size_t len;
	struct wpabuf *e;

	pos = os_strchr(cmd, ' ');
	if (pos == NULL)
		return -1;
	*pos++ = '\0';

	len = os_strlen(pos);
	if (len & 1)
		return -1;
	len /= 2;

	if (os_strcmp(cmd, "all") == 0) {
		int res;

		e = wpabuf_alloc(len);
		if (e == NULL)
			return -1;
		if (hexstr2bin(pos, wpabuf_put(e, len), len) < 0) {
			wpabuf_free(e);
			return -1;
		}
		res = wifi_display_subelem_set_from_ies(global, e);
		wpabuf_free(e);
		return res;
	}

	subelem = atoi(cmd);
	if (subelem < 0 || subelem >= MAX_WFD_SUBELEMS)
		return -1;

	if (len == 0) {
		/* Clear subelement */
		e = NULL;
		wpa_printf(MSG_DEBUG, "WFD: Clear subelement %d", subelem);
	} else {
		e = wpabuf_alloc(1 + len);
		if (e == NULL)
			return -1;
		wpabuf_put_u8(e, subelem);
		if (hexstr2bin(pos, wpabuf_put(e, len), len) < 0) {
			wpabuf_free(e);
			return -1;
		}
		wpa_printf(MSG_DEBUG, "WFD: Set subelement %d", subelem);
	}

	wpabuf_free(global->wfd_subelem[subelem]);
	global->wfd_subelem[subelem] = e;
	wifi_display_update_wfd_ie(global);

	return 0;
}