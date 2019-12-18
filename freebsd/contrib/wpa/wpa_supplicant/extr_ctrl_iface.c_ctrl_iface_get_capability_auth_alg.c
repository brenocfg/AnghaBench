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
struct wpa_supplicant {int drv_flags; } ;
struct wpa_driver_capa {int auth; } ;

/* Variables and functions */
 int WPA_DRIVER_AUTH_LEAP ; 
 int WPA_DRIVER_AUTH_OPEN ; 
 int WPA_DRIVER_AUTH_SHARED ; 
 int WPA_DRIVER_FLAGS_SAE ; 
 int os_snprintf (char*,int,char*,char*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 size_t os_strlcpy (char*,char*,size_t) ; 
 scalar_t__ wpa_is_fils_sk_pfs_supported (struct wpa_supplicant*) ; 
 scalar_t__ wpa_is_fils_supported (struct wpa_supplicant*) ; 

__attribute__((used)) static int ctrl_iface_get_capability_auth_alg(struct wpa_supplicant *wpa_s,
					      int res, char *strict,
					      struct wpa_driver_capa *capa,
					      char *buf, size_t buflen)
{
	int ret;
	char *pos, *end;
	size_t len;

	pos = buf;
	end = pos + buflen;

	if (res < 0) {
		if (strict)
			return 0;
		len = os_strlcpy(buf, "OPEN SHARED LEAP", buflen);
		if (len >= buflen)
			return -1;
		return len;
	}

	if (capa->auth & (WPA_DRIVER_AUTH_OPEN)) {
		ret = os_snprintf(pos, end - pos, "%sOPEN",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (capa->auth & (WPA_DRIVER_AUTH_SHARED)) {
		ret = os_snprintf(pos, end - pos, "%sSHARED",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (capa->auth & (WPA_DRIVER_AUTH_LEAP)) {
		ret = os_snprintf(pos, end - pos, "%sLEAP",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

#ifdef CONFIG_SAE
	if (wpa_s->drv_flags & WPA_DRIVER_FLAGS_SAE) {
		ret = os_snprintf(pos, end - pos, "%sSAE",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#endif /* CONFIG_SAE */

#ifdef CONFIG_FILS
	if (wpa_is_fils_supported(wpa_s)) {
		ret = os_snprintf(pos, end - pos, "%sFILS_SK_WITHOUT_PFS",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

#ifdef CONFIG_FILS_SK_PFS
	if (wpa_is_fils_sk_pfs_supported(wpa_s)) {
		ret = os_snprintf(pos, end - pos, "%sFILS_SK_WITH_PFS",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#endif /* CONFIG_FILS_SK_PFS */
#endif /* CONFIG_FILS */

	return pos - buf;
}