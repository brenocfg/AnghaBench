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
struct wps_er_ap {int /*<<< orphan*/  (* m1_handler ) (struct wps_er_ap*,struct wpabuf*) ;} ;
struct wpabuf {int dummy; } ;
typedef  enum http_reply_code { ____Placeholder_http_reply_code } http_reply_code ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  stub1 (struct wps_er_ap*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 struct wpabuf* xml_get_base64_item (char const*,char*,int*) ; 

__attribute__((used)) static void wps_er_ap_learn(struct wps_er_ap *ap, const char *dev_info)
{
	struct wpabuf *info;
	enum http_reply_code ret;

	wpa_printf(MSG_DEBUG, "WPS ER: Received GetDeviceInfo response (M1) "
		   "from the AP");
	info = xml_get_base64_item(dev_info, "NewDeviceInfo", &ret);
	if (info == NULL) {
		wpa_printf(MSG_DEBUG, "WPS ER: Could not extract "
			   "NewDeviceInfo from GetDeviceInfo response");
		return;
	}

	ap->m1_handler(ap, info);
	wpabuf_free(info);
}