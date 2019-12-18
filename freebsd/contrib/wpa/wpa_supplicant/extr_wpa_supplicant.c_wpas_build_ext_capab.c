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
typedef  size_t u8 ;
struct wpa_supplicant {size_t extended_capa_len; size_t* extended_capa_mask; size_t* extended_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WLAN_EID_EXT_CAPAB ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_ext_capab_byte (struct wpa_supplicant*,size_t*,size_t) ; 

int wpas_build_ext_capab(struct wpa_supplicant *wpa_s, u8 *buf, size_t buflen)
{
	u8 *pos = buf;
	u8 len = 10, i;

	if (len < wpa_s->extended_capa_len)
		len = wpa_s->extended_capa_len;
	if (buflen < (size_t) len + 2) {
		wpa_printf(MSG_INFO,
			   "Not enough room for building extended capabilities element");
		return -1;
	}

	*pos++ = WLAN_EID_EXT_CAPAB;
	*pos++ = len;
	for (i = 0; i < len; i++, pos++) {
		wpas_ext_capab_byte(wpa_s, pos, i);

		if (i < wpa_s->extended_capa_len) {
			*pos &= ~wpa_s->extended_capa_mask[i];
			*pos |= wpa_s->extended_capa[i];
		}
	}

	while (len > 0 && buf[1 + len] == 0) {
		len--;
		buf[1] = len;
	}
	if (len == 0)
		return 0;

	return 2 + len;
}