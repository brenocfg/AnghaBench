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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct wpa_supplicant {scalar_t__ p2p_group_interface; int enable_oce; } ;
typedef  int /*<<< orphan*/  ext_capab ;
typedef  enum wpa_driver_if_type { ____Placeholder_wpa_driver_if_type } wpa_driver_if_type ;

/* Variables and functions */
 int OCE_STA ; 
 scalar_t__ P2P_GROUP_INTERFACE_CLIENT ; 
 int WPA_IF_P2P_CLIENT ; 
 int WPA_IF_STATION ; 
 int /*<<< orphan*/  wpa_drv_get_ext_capa (struct wpa_supplicant*,int) ; 
 int /*<<< orphan*/  wpa_drv_set_default_scan_ies (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ wpabuf_resize (struct wpabuf**,int) ; 
 int wpas_build_ext_capab (struct wpa_supplicant*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpas_fils_req_param_add_max_channel (struct wpa_supplicant*,struct wpabuf**) ; 
 int /*<<< orphan*/  wpas_mbo_scan_ie (struct wpa_supplicant*,struct wpabuf*) ; 

void wpa_supplicant_set_default_scan_ies(struct wpa_supplicant *wpa_s)
{
	struct wpabuf *default_ies = NULL;
	u8 ext_capab[18];
	int ext_capab_len;
	enum wpa_driver_if_type type = WPA_IF_STATION;

#ifdef CONFIG_P2P
	if (wpa_s->p2p_group_interface == P2P_GROUP_INTERFACE_CLIENT)
		type = WPA_IF_P2P_CLIENT;
#endif /* CONFIG_P2P */

	wpa_drv_get_ext_capa(wpa_s, type);

	ext_capab_len = wpas_build_ext_capab(wpa_s, ext_capab,
					     sizeof(ext_capab));
	if (ext_capab_len > 0 &&
	    wpabuf_resize(&default_ies, ext_capab_len) == 0)
		wpabuf_put_data(default_ies, ext_capab, ext_capab_len);

#ifdef CONFIG_MBO
	if (wpa_s->enable_oce & OCE_STA)
		wpas_fils_req_param_add_max_channel(wpa_s, &default_ies);
	/* Send MBO and OCE capabilities */
	if (wpabuf_resize(&default_ies, 12) == 0)
		wpas_mbo_scan_ie(wpa_s, default_ies);
#endif /* CONFIG_MBO */

	if (default_ies)
		wpa_drv_set_default_scan_ies(wpa_s, wpabuf_head(default_ies),
					     wpabuf_len(default_ies));
	wpabuf_free(default_ies);
}