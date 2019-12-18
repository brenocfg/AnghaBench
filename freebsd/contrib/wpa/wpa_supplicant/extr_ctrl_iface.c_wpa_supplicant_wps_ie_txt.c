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
struct wpa_supplicant {int dummy; } ;
struct wpa_bss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPS_IE_VENDOR_TYPE ; 
 struct wpabuf* wpa_bss_get_vendor_ie_multi (struct wpa_bss const*,int /*<<< orphan*/ ) ; 
 char* wpa_supplicant_wps_ie_txt_buf (struct wpa_supplicant*,char*,char*,struct wpabuf*) ; 

__attribute__((used)) static char * wpa_supplicant_wps_ie_txt(struct wpa_supplicant *wpa_s,
					char *pos, char *end,
					const struct wpa_bss *bss)
{
#ifdef CONFIG_WPS
	struct wpabuf *wps_ie;
	wps_ie = wpa_bss_get_vendor_ie_multi(bss, WPS_IE_VENDOR_TYPE);
	return wpa_supplicant_wps_ie_txt_buf(wpa_s, pos, end, wps_ie);
#else /* CONFIG_WPS */
	return pos;
#endif /* CONFIG_WPS */
}