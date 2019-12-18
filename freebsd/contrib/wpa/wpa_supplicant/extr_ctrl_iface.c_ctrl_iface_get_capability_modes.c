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
struct wpa_driver_capa {int flags; } ;

/* Variables and functions */
 int WPA_DRIVER_FLAGS_AP ; 
 int WPA_DRIVER_FLAGS_IBSS ; 
 int WPA_DRIVER_FLAGS_MESH ; 
 int os_snprintf (char*,int,char*,char*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 size_t os_strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int ctrl_iface_get_capability_modes(int res, char *strict,
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
		len = os_strlcpy(buf, "IBSS AP", buflen);
		if (len >= buflen)
			return -1;
		return len;
	}

	if (capa->flags & WPA_DRIVER_FLAGS_IBSS) {
		ret = os_snprintf(pos, end - pos, "%sIBSS",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (capa->flags & WPA_DRIVER_FLAGS_AP) {
		ret = os_snprintf(pos, end - pos, "%sAP",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

#ifdef CONFIG_MESH
	if (capa->flags & WPA_DRIVER_FLAGS_MESH) {
		ret = os_snprintf(pos, end - pos, "%sMESH",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#endif /* CONFIG_MESH */

	return pos - buf;
}