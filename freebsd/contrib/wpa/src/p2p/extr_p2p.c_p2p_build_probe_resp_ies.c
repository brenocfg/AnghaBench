#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct p2p_data {int dev_capab; int /*<<< orphan*/  p2ps_adv_list; int /*<<< orphan*/  ext_listen_interval; int /*<<< orphan*/  ext_listen_period; scalar_t__* vendor_elem; scalar_t__ wfd_ie_probe_resp; TYPE_1__* go_neg_peer; } ;
struct TYPE_2__ {int /*<<< orphan*/  wps_method; } ;

/* Variables and functions */
 scalar_t__ MAX_SVC_ADV_IE_LEN ; 
 int P2P_DEV_CAPAB_CLIENT_DISCOVERABILITY ; 
 size_t VENDOR_ELEM_PROBE_RESP_P2P ; 
 int /*<<< orphan*/  p2p_buf_add_capability (struct wpabuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_buf_add_device_info (struct wpabuf*,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_buf_add_ext_listen_timing (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p2p_buf_add_ie_hdr (struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_buf_add_service_instance (struct wpabuf*,struct p2p_data*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_buf_update_ie_hdr (struct wpabuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ p2p_build_wps_ie (struct p2p_data*,struct wpabuf*,int,int) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 int p2p_wps_method_pw_id (int /*<<< orphan*/ ) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 size_t wpabuf_len (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,scalar_t__) ; 

struct wpabuf * p2p_build_probe_resp_ies(struct p2p_data *p2p,
					 const u8 *query_hash,
					 u8 query_count)
{
	struct wpabuf *buf;
	u8 *len;
	int pw_id = -1;
	size_t extra = 0;

#ifdef CONFIG_WIFI_DISPLAY
	if (p2p->wfd_ie_probe_resp)
		extra = wpabuf_len(p2p->wfd_ie_probe_resp);
#endif /* CONFIG_WIFI_DISPLAY */

	if (p2p->vendor_elem && p2p->vendor_elem[VENDOR_ELEM_PROBE_RESP_P2P])
		extra += wpabuf_len(p2p->vendor_elem[VENDOR_ELEM_PROBE_RESP_P2P]);

	if (query_count)
		extra += MAX_SVC_ADV_IE_LEN;

	buf = wpabuf_alloc(1000 + extra);
	if (buf == NULL)
		return NULL;

	if (p2p->go_neg_peer) {
		/* Advertise immediate availability of WPS credential */
		pw_id = p2p_wps_method_pw_id(p2p->go_neg_peer->wps_method);
	}

	if (p2p_build_wps_ie(p2p, buf, pw_id, 1) < 0) {
		p2p_dbg(p2p, "Failed to build WPS IE for Probe Response");
		wpabuf_free(buf);
		return NULL;
	}

#ifdef CONFIG_WIFI_DISPLAY
	if (p2p->wfd_ie_probe_resp)
		wpabuf_put_buf(buf, p2p->wfd_ie_probe_resp);
#endif /* CONFIG_WIFI_DISPLAY */

	if (p2p->vendor_elem && p2p->vendor_elem[VENDOR_ELEM_PROBE_RESP_P2P])
		wpabuf_put_buf(buf,
			       p2p->vendor_elem[VENDOR_ELEM_PROBE_RESP_P2P]);

	/* P2P IE */
	len = p2p_buf_add_ie_hdr(buf);
	p2p_buf_add_capability(buf, p2p->dev_capab &
			       ~P2P_DEV_CAPAB_CLIENT_DISCOVERABILITY, 0);
	if (p2p->ext_listen_interval)
		p2p_buf_add_ext_listen_timing(buf, p2p->ext_listen_period,
					      p2p->ext_listen_interval);
	p2p_buf_add_device_info(buf, p2p, NULL);
	p2p_buf_update_ie_hdr(buf, len);

	if (query_count) {
		p2p_buf_add_service_instance(buf, p2p, query_count, query_hash,
					     p2p->p2ps_adv_list);
	}

	return buf;
}