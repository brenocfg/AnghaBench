#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct wpa_supplicant {scalar_t__ p2p_group_interface; int enable_oce; struct wpabuf** vendor_elem; struct wpabuf* fst_ies; TYPE_3__* conf; TYPE_2__* global; TYPE_1__* wps; } ;
typedef  int /*<<< orphan*/  ext_capab ;
typedef  enum wps_request_type { ____Placeholder_wps_request_type } wps_request_type ;
struct TYPE_6__ {scalar_t__ hs20; scalar_t__ interworking; } ;
struct TYPE_5__ {int /*<<< orphan*/  p2p; } ;
struct TYPE_4__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PW_DEFAULT ; 
 int /*<<< orphan*/  DEV_PW_PUSHBUTTON ; 
 int OCE_STA ; 
 scalar_t__ P2P_GROUP_INTERFACE_CLIENT ; 
 size_t VENDOR_ELEM_PROBE_REQ ; 
 int /*<<< orphan*/  WPA_IF_P2P_CLIENT ; 
 int /*<<< orphan*/  WPA_IF_STATION ; 
 int WPS_REQ_ENROLLEE_INFO ; 
 size_t p2p_scan_ie_buf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_drv_get_ext_capa (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_mesh_add_scan_ie (struct wpa_supplicant*,struct wpabuf**) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ wpabuf_resize (struct wpabuf**,int) ; 
 int /*<<< orphan*/  wpas_add_interworking_elements (struct wpa_supplicant*,struct wpabuf*) ; 
 int wpas_build_ext_capab (struct wpa_supplicant*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpas_fils_req_param_add_max_channel (struct wpa_supplicant*,struct wpabuf**) ; 
 int /*<<< orphan*/  wpas_hs20_add_indication (struct wpabuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_mbo_scan_ie (struct wpa_supplicant*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpas_p2p_scan_ie (struct wpa_supplicant*,struct wpabuf*) ; 
 int wpas_wps_in_use (struct wpa_supplicant*,int*) ; 
 struct wpabuf* wps_build_probe_req_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct wpabuf * wpa_supplicant_extra_ies(struct wpa_supplicant *wpa_s)
{
	struct wpabuf *extra_ie = NULL;
	u8 ext_capab[18];
	int ext_capab_len;
#ifdef CONFIG_WPS
	int wps = 0;
	enum wps_request_type req_type = WPS_REQ_ENROLLEE_INFO;
#endif /* CONFIG_WPS */

#ifdef CONFIG_P2P
	if (wpa_s->p2p_group_interface == P2P_GROUP_INTERFACE_CLIENT)
		wpa_drv_get_ext_capa(wpa_s, WPA_IF_P2P_CLIENT);
	else
#endif /* CONFIG_P2P */
		wpa_drv_get_ext_capa(wpa_s, WPA_IF_STATION);

	ext_capab_len = wpas_build_ext_capab(wpa_s, ext_capab,
					     sizeof(ext_capab));
	if (ext_capab_len > 0 &&
	    wpabuf_resize(&extra_ie, ext_capab_len) == 0)
		wpabuf_put_data(extra_ie, ext_capab, ext_capab_len);

#ifdef CONFIG_INTERWORKING
	if (wpa_s->conf->interworking &&
	    wpabuf_resize(&extra_ie, 100) == 0)
		wpas_add_interworking_elements(wpa_s, extra_ie);
#endif /* CONFIG_INTERWORKING */

#ifdef CONFIG_MBO
	if (wpa_s->enable_oce & OCE_STA)
		wpas_fils_req_param_add_max_channel(wpa_s, &extra_ie);
#endif /* CONFIG_MBO */

#ifdef CONFIG_WPS
	wps = wpas_wps_in_use(wpa_s, &req_type);

	if (wps) {
		struct wpabuf *wps_ie;
		wps_ie = wps_build_probe_req_ie(wps == 2 ? DEV_PW_PUSHBUTTON :
						DEV_PW_DEFAULT,
						&wpa_s->wps->dev,
						wpa_s->wps->uuid, req_type,
						0, NULL);
		if (wps_ie) {
			if (wpabuf_resize(&extra_ie, wpabuf_len(wps_ie)) == 0)
				wpabuf_put_buf(extra_ie, wps_ie);
			wpabuf_free(wps_ie);
		}
	}

#ifdef CONFIG_P2P
	if (wps) {
		size_t ielen = p2p_scan_ie_buf_len(wpa_s->global->p2p);
		if (wpabuf_resize(&extra_ie, ielen) == 0)
			wpas_p2p_scan_ie(wpa_s, extra_ie);
	}
#endif /* CONFIG_P2P */

	wpa_supplicant_mesh_add_scan_ie(wpa_s, &extra_ie);

#endif /* CONFIG_WPS */

#ifdef CONFIG_HS20
	if (wpa_s->conf->hs20 && wpabuf_resize(&extra_ie, 9) == 0)
		wpas_hs20_add_indication(extra_ie, -1, 0);
#endif /* CONFIG_HS20 */

#ifdef CONFIG_FST
	if (wpa_s->fst_ies &&
	    wpabuf_resize(&extra_ie, wpabuf_len(wpa_s->fst_ies)) == 0)
		wpabuf_put_buf(extra_ie, wpa_s->fst_ies);
#endif /* CONFIG_FST */

#ifdef CONFIG_MBO
	/* Send MBO and OCE capabilities */
	if (wpabuf_resize(&extra_ie, 12) == 0)
		wpas_mbo_scan_ie(wpa_s, extra_ie);
#endif /* CONFIG_MBO */

	if (wpa_s->vendor_elem[VENDOR_ELEM_PROBE_REQ]) {
		struct wpabuf *buf = wpa_s->vendor_elem[VENDOR_ELEM_PROBE_REQ];

		if (wpabuf_resize(&extra_ie, wpabuf_len(buf)) == 0)
			wpabuf_put_buf(extra_ie, buf);
	}

	return extra_ie;
}