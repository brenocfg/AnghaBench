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
struct wpabuf {size_t used; } ;
struct wpa_global {int /*<<< orphan*/ * p2p; int /*<<< orphan*/ ** wfd_subelem; int /*<<< orphan*/  wifi_display; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t WFD_SUBELEM_ASSOCIATED_BSSID ; 
 size_t WFD_SUBELEM_COUPLED_SINK ; 
 size_t WFD_SUBELEM_DEVICE_INFO ; 
 size_t WFD_SUBELEM_EXT_CAPAB ; 
 size_t WFD_SUBELEM_R2_DEVICE_INFO ; 
 size_t WFD_SUBELEM_SESSION_INFO ; 
 int /*<<< orphan*/  p2p_set_wfd_assoc_bssid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_set_wfd_coupled_sink_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_set_wfd_dev_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_set_wfd_ie_assoc_req (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_set_wfd_ie_beacon (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_set_wfd_ie_go_neg (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_set_wfd_ie_invitation (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_set_wfd_ie_probe_req (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_set_wfd_ie_probe_resp (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_set_wfd_ie_prov_disc_req (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_set_wfd_ie_prov_disc_resp (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_set_wfd_r2_dev_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wpabuf* wifi_display_encaps (struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wifi_display_update_wfd_ie(struct wpa_global *global)
{
	struct wpabuf *ie, *buf;
	size_t len, plen;

	if (global->p2p == NULL)
		return 0;

	wpa_printf(MSG_DEBUG, "WFD: Update WFD IE");

	if (!global->wifi_display) {
		wpa_printf(MSG_DEBUG, "WFD: Wi-Fi Display disabled - do not "
			   "include WFD IE");
		p2p_set_wfd_ie_beacon(global->p2p, NULL);
		p2p_set_wfd_ie_probe_req(global->p2p, NULL);
		p2p_set_wfd_ie_probe_resp(global->p2p, NULL);
		p2p_set_wfd_ie_assoc_req(global->p2p, NULL);
		p2p_set_wfd_ie_invitation(global->p2p, NULL);
		p2p_set_wfd_ie_prov_disc_req(global->p2p, NULL);
		p2p_set_wfd_ie_prov_disc_resp(global->p2p, NULL);
		p2p_set_wfd_ie_go_neg(global->p2p, NULL);
		p2p_set_wfd_dev_info(global->p2p, NULL);
		p2p_set_wfd_r2_dev_info(global->p2p, NULL);
		p2p_set_wfd_assoc_bssid(global->p2p, NULL);
		p2p_set_wfd_coupled_sink_info(global->p2p, NULL);
		return 0;
	}

	p2p_set_wfd_dev_info(global->p2p,
			     global->wfd_subelem[WFD_SUBELEM_DEVICE_INFO]);
	p2p_set_wfd_r2_dev_info(
		global->p2p, global->wfd_subelem[WFD_SUBELEM_R2_DEVICE_INFO]);
	p2p_set_wfd_assoc_bssid(
		global->p2p,
		global->wfd_subelem[WFD_SUBELEM_ASSOCIATED_BSSID]);
	p2p_set_wfd_coupled_sink_info(
		global->p2p, global->wfd_subelem[WFD_SUBELEM_COUPLED_SINK]);

	/*
	 * WFD IE is included in number of management frames. Two different
	 * sets of subelements are included depending on the frame:
	 *
	 * Beacon, (Re)Association Request, GO Negotiation Req/Resp/Conf,
	 * Provision Discovery Req:
	 * WFD Device Info
	 * [Associated BSSID]
	 * [Coupled Sink Info]
	 *
	 * Probe Request:
	 * WFD Device Info
	 * [Associated BSSID]
	 * [Coupled Sink Info]
	 * [WFD Extended Capability]
	 *
	 * Probe Response:
	 * WFD Device Info
	 * [Associated BSSID]
	 * [Coupled Sink Info]
	 * [WFD Extended Capability]
	 * [WFD Session Info]
	 *
	 * (Re)Association Response, P2P Invitation Req/Resp,
	 * Provision Discovery Resp:
	 * WFD Device Info
	 * [Associated BSSID]
	 * [Coupled Sink Info]
	 * [WFD Session Info]
	 */
	len = 0;
	if (global->wfd_subelem[WFD_SUBELEM_DEVICE_INFO])
		len += wpabuf_len(global->wfd_subelem[
					  WFD_SUBELEM_DEVICE_INFO]);

	if (global->wfd_subelem[WFD_SUBELEM_R2_DEVICE_INFO])
		len += wpabuf_len(global->wfd_subelem[
					  WFD_SUBELEM_R2_DEVICE_INFO]);

	if (global->wfd_subelem[WFD_SUBELEM_ASSOCIATED_BSSID])
		len += wpabuf_len(global->wfd_subelem[
					  WFD_SUBELEM_ASSOCIATED_BSSID]);
	if (global->wfd_subelem[WFD_SUBELEM_COUPLED_SINK])
		len += wpabuf_len(global->wfd_subelem[
					  WFD_SUBELEM_COUPLED_SINK]);
	if (global->wfd_subelem[WFD_SUBELEM_SESSION_INFO])
		len += wpabuf_len(global->wfd_subelem[
					  WFD_SUBELEM_SESSION_INFO]);
	if (global->wfd_subelem[WFD_SUBELEM_EXT_CAPAB])
		len += wpabuf_len(global->wfd_subelem[WFD_SUBELEM_EXT_CAPAB]);
	buf = wpabuf_alloc(len);
	if (buf == NULL)
		return -1;

	if (global->wfd_subelem[WFD_SUBELEM_DEVICE_INFO])
		wpabuf_put_buf(buf,
			       global->wfd_subelem[WFD_SUBELEM_DEVICE_INFO]);

	if (global->wfd_subelem[WFD_SUBELEM_R2_DEVICE_INFO])
		wpabuf_put_buf(buf,
			       global->wfd_subelem[WFD_SUBELEM_R2_DEVICE_INFO]);

	if (global->wfd_subelem[WFD_SUBELEM_ASSOCIATED_BSSID])
		wpabuf_put_buf(buf, global->wfd_subelem[
				       WFD_SUBELEM_ASSOCIATED_BSSID]);
	if (global->wfd_subelem[WFD_SUBELEM_COUPLED_SINK])
		wpabuf_put_buf(buf,
			       global->wfd_subelem[WFD_SUBELEM_COUPLED_SINK]);

	ie = wifi_display_encaps(buf);
	wpa_hexdump_buf(MSG_DEBUG, "WFD: WFD IE for Beacon", ie);
	p2p_set_wfd_ie_beacon(global->p2p, ie);

	ie = wifi_display_encaps(buf);
	wpa_hexdump_buf(MSG_DEBUG, "WFD: WFD IE for (Re)Association Request",
			ie);
	p2p_set_wfd_ie_assoc_req(global->p2p, ie);

	ie = wifi_display_encaps(buf);
	wpa_hexdump_buf(MSG_DEBUG, "WFD: WFD IE for GO Negotiation", ie);
	p2p_set_wfd_ie_go_neg(global->p2p, ie);

	ie = wifi_display_encaps(buf);
	wpa_hexdump_buf(MSG_DEBUG, "WFD: WFD IE for Provision Discovery "
			"Request", ie);
	p2p_set_wfd_ie_prov_disc_req(global->p2p, ie);

	plen = buf->used;
	if (global->wfd_subelem[WFD_SUBELEM_EXT_CAPAB])
		wpabuf_put_buf(buf,
			       global->wfd_subelem[WFD_SUBELEM_EXT_CAPAB]);

	ie = wifi_display_encaps(buf);
	wpa_hexdump_buf(MSG_DEBUG, "WFD: WFD IE for Probe Request", ie);
	p2p_set_wfd_ie_probe_req(global->p2p, ie);

	if (global->wfd_subelem[WFD_SUBELEM_SESSION_INFO])
		wpabuf_put_buf(buf,
			       global->wfd_subelem[WFD_SUBELEM_SESSION_INFO]);
	ie = wifi_display_encaps(buf);
	wpa_hexdump_buf(MSG_DEBUG, "WFD: WFD IE for Probe Response", ie);
	p2p_set_wfd_ie_probe_resp(global->p2p, ie);

	/* Remove WFD Extended Capability from buffer */
	buf->used = plen;
	if (global->wfd_subelem[WFD_SUBELEM_SESSION_INFO])
		wpabuf_put_buf(buf,
			       global->wfd_subelem[WFD_SUBELEM_SESSION_INFO]);

	ie = wifi_display_encaps(buf);
	wpa_hexdump_buf(MSG_DEBUG, "WFD: WFD IE for P2P Invitation", ie);
	p2p_set_wfd_ie_invitation(global->p2p, ie);

	ie = wifi_display_encaps(buf);
	wpa_hexdump_buf(MSG_DEBUG, "WFD: WFD IE for Provision Discovery "
			"Response", ie);
	p2p_set_wfd_ie_prov_disc_resp(global->p2p, ie);

	wpabuf_free(buf);

	return 0;
}