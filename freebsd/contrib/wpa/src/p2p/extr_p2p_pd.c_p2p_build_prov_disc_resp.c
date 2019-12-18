#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;
struct p2ps_provision {int conncap; int status; int /*<<< orphan*/  adv_mac; int /*<<< orphan*/  session_mac; int /*<<< orphan*/  session_id; int /*<<< orphan*/  adv_id; } ;
struct p2p_group {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  p2p_device_addr; } ;
struct p2p_device {TYPE_1__ info; } ;
struct p2p_data {size_t num_groups; int dev_capab; struct wpabuf** vendor_elem; struct p2ps_provision* p2ps_prov; int /*<<< orphan*/  client_timeout; int /*<<< orphan*/  go_timeout; int /*<<< orphan*/  channels; TYPE_2__* cfg; int /*<<< orphan*/  op_channel; int /*<<< orphan*/  op_reg_class; scalar_t__ cross_connect; struct p2p_group** groups; struct wpabuf* wfd_ie_prov_disc_resp; } ;
typedef  enum p2p_status_code { ____Placeholder_p2p_status_code } p2p_status_code ;
struct TYPE_4__ {int (* get_persistent_group ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,size_t,int*,int*,size_t*,int*) ;int /*<<< orphan*/  country; int /*<<< orphan*/  op_channel; int /*<<< orphan*/  op_reg_class; int /*<<< orphan*/  cb_ctx; scalar_t__ p2p_intra_bss; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int P2PS_SETUP_CLIENT ; 
 int P2PS_SETUP_GROUP_OWNER ; 
 int P2P_DEV_CAPAB_CLIENT_DISCOVERABILITY ; 
 int P2P_GROUP_CAPAB_CROSS_CONN ; 
 int P2P_GROUP_CAPAB_INTRA_BSS_DIST ; 
 int P2P_GROUP_CAPAB_PERSISTENT_GROUP ; 
 int P2P_GROUP_CAPAB_PERSISTENT_RECONN ; 
 int /*<<< orphan*/  P2P_PROV_DISC_RESP ; 
 int P2P_SC_SUCCESS ; 
 int P2P_SC_SUCCESS_DEFERRED ; 
 int SSID_MAX_LEN ; 
 size_t VENDOR_ELEM_P2P_PD_RESP ; 
 int /*<<< orphan*/  is_zero_ether_addr (int*) ; 
 int /*<<< orphan*/  p2p_buf_add_advertisement_id (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_buf_add_capability (struct wpabuf*,int,int) ; 
 int /*<<< orphan*/  p2p_buf_add_channel_list (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_buf_add_config_timeout (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_buf_add_connection_capability (struct wpabuf*,int) ; 
 int /*<<< orphan*/  p2p_buf_add_device_info (struct wpabuf*,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_buf_add_feature_capability (struct wpabuf*,int /*<<< orphan*/ ,int const*) ; 
 int* p2p_buf_add_ie_hdr (struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_buf_add_intended_addr (struct wpabuf*,int*) ; 
 int /*<<< orphan*/  p2p_buf_add_operating_channel (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_buf_add_persistent_group_info (struct wpabuf*,int*,int*,size_t) ; 
 int /*<<< orphan*/  p2p_buf_add_public_action_hdr (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p2p_buf_add_session_id (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_buf_add_status (struct wpabuf*,int) ; 
 int /*<<< orphan*/  p2p_buf_update_ie_hdr (struct wpabuf*,int*) ; 
 int /*<<< orphan*/  p2p_build_wps_ie_config_methods (struct wpabuf*,int /*<<< orphan*/ ) ; 
 struct wpabuf* p2p_group_get_wfd_ie (struct p2p_group*) ; 
 int /*<<< orphan*/  p2p_group_is_group_id_match (struct p2p_group*,int const*,size_t) ; 
 int /*<<< orphan*/  p2ps_add_new_group_info (struct p2p_data*,struct p2p_device*,struct wpabuf*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,size_t,int*,int*,size_t*,int*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * p2p_build_prov_disc_resp(struct p2p_data *p2p,
						struct p2p_device *dev,
						u8 dialog_token,
						enum p2p_status_code status,
						u16 config_methods,
						u32 adv_id,
						const u8 *group_id,
						size_t group_id_len,
						const u8 *persist_ssid,
						size_t persist_ssid_len,
						const u8 *fcap,
						u16 fcap_len)
{
	struct wpabuf *buf;
	size_t extra = 0;
	int persist = 0;

#ifdef CONFIG_WIFI_DISPLAY
	struct wpabuf *wfd_ie = p2p->wfd_ie_prov_disc_resp;
	if (wfd_ie && group_id) {
		size_t i;
		for (i = 0; i < p2p->num_groups; i++) {
			struct p2p_group *g = p2p->groups[i];
			struct wpabuf *ie;
			if (!p2p_group_is_group_id_match(g, group_id,
							 group_id_len))
				continue;
			ie = p2p_group_get_wfd_ie(g);
			if (ie) {
				wfd_ie = ie;
				break;
			}
		}
	}
	if (wfd_ie)
		extra = wpabuf_len(wfd_ie);
#endif /* CONFIG_WIFI_DISPLAY */

	if (p2p->vendor_elem && p2p->vendor_elem[VENDOR_ELEM_P2P_PD_RESP])
		extra += wpabuf_len(p2p->vendor_elem[VENDOR_ELEM_P2P_PD_RESP]);

	buf = wpabuf_alloc(1000 + extra);
	if (buf == NULL)
		return NULL;

	p2p_buf_add_public_action_hdr(buf, P2P_PROV_DISC_RESP, dialog_token);

	/* Add P2P IE for P2PS */
	if (p2p->p2ps_prov && p2p->p2ps_prov->adv_id == adv_id) {
		u8 *len = p2p_buf_add_ie_hdr(buf);
		struct p2ps_provision *prov = p2p->p2ps_prov;
		u8 group_capab;
		u8 conncap = 0;

		if (status == P2P_SC_SUCCESS ||
		    status == P2P_SC_SUCCESS_DEFERRED)
			conncap = prov->conncap;

		if (!status && prov->status != -1)
			status = prov->status;

		p2p_buf_add_status(buf, status);
		group_capab = P2P_GROUP_CAPAB_PERSISTENT_GROUP |
			P2P_GROUP_CAPAB_PERSISTENT_RECONN;
		if (p2p->cross_connect)
			group_capab |= P2P_GROUP_CAPAB_CROSS_CONN;
		if (p2p->cfg->p2p_intra_bss)
			group_capab |= P2P_GROUP_CAPAB_INTRA_BSS_DIST;
		p2p_buf_add_capability(buf, p2p->dev_capab &
				       ~P2P_DEV_CAPAB_CLIENT_DISCOVERABILITY,
				       group_capab);
		p2p_buf_add_device_info(buf, p2p, NULL);

		if (persist_ssid && p2p->cfg->get_persistent_group && dev &&
		    (status == P2P_SC_SUCCESS ||
		     status == P2P_SC_SUCCESS_DEFERRED)) {
			u8 ssid[SSID_MAX_LEN];
			size_t ssid_len;
			u8 go_dev_addr[ETH_ALEN];
			u8 intended_addr[ETH_ALEN];

			persist = p2p->cfg->get_persistent_group(
				p2p->cfg->cb_ctx,
				dev->info.p2p_device_addr,
				persist_ssid, persist_ssid_len, go_dev_addr,
				ssid, &ssid_len, intended_addr);
			if (persist) {
				p2p_buf_add_persistent_group_info(
					buf, go_dev_addr, ssid, ssid_len);
				if (!is_zero_ether_addr(intended_addr))
					p2p_buf_add_intended_addr(
						buf, intended_addr);
			}
		}

		if (!persist && (conncap & P2PS_SETUP_GROUP_OWNER))
			p2ps_add_new_group_info(p2p, dev, buf);

		/* Add Operating Channel if conncap indicates GO */
		if (persist || (conncap & P2PS_SETUP_GROUP_OWNER)) {
			if (p2p->op_reg_class && p2p->op_channel)
				p2p_buf_add_operating_channel(
					buf, p2p->cfg->country,
					p2p->op_reg_class,
					p2p->op_channel);
			else
				p2p_buf_add_operating_channel(
					buf, p2p->cfg->country,
					p2p->cfg->op_reg_class,
					p2p->cfg->op_channel);
		}

		if (persist ||
		    (conncap & (P2PS_SETUP_CLIENT | P2PS_SETUP_GROUP_OWNER)))
			p2p_buf_add_channel_list(buf, p2p->cfg->country,
						 &p2p->channels);

		if (!persist && conncap)
			p2p_buf_add_connection_capability(buf, conncap);

		p2p_buf_add_advertisement_id(buf, adv_id, prov->adv_mac);

		if (persist ||
		    (conncap & (P2PS_SETUP_CLIENT | P2PS_SETUP_GROUP_OWNER)))
			p2p_buf_add_config_timeout(buf, p2p->go_timeout,
						   p2p->client_timeout);

		p2p_buf_add_session_id(buf, prov->session_id,
				       prov->session_mac);

		p2p_buf_add_feature_capability(buf, fcap_len, fcap);
		p2p_buf_update_ie_hdr(buf, len);
	} else if (status != P2P_SC_SUCCESS || adv_id) {
		u8 *len = p2p_buf_add_ie_hdr(buf);

		p2p_buf_add_status(buf, status);

		if (p2p->p2ps_prov)
			p2p_buf_add_advertisement_id(buf, adv_id,
						     p2p->p2ps_prov->adv_mac);

		p2p_buf_update_ie_hdr(buf, len);
	}

	/* WPS IE with Config Methods attribute */
	p2p_build_wps_ie_config_methods(buf, config_methods);

#ifdef CONFIG_WIFI_DISPLAY
	if (wfd_ie)
		wpabuf_put_buf(buf, wfd_ie);
#endif /* CONFIG_WIFI_DISPLAY */

	if (p2p->vendor_elem && p2p->vendor_elem[VENDOR_ELEM_P2P_PD_RESP])
		wpabuf_put_buf(buf, p2p->vendor_elem[VENDOR_ELEM_P2P_PD_RESP]);

	return buf;
}