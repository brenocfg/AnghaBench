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
struct TYPE_4__ {struct p2p_data* range; } ;
struct p2p_data {TYPE_2__ no_go_freq; int /*<<< orphan*/  sd_resp; struct p2p_data* groups; TYPE_1__* cfg; int /*<<< orphan*/  wfd_r2_dev_info; int /*<<< orphan*/  wfd_coupled_sink_info; int /*<<< orphan*/  wfd_assoc_bssid; int /*<<< orphan*/  wfd_dev_info; int /*<<< orphan*/  wfd_ie_go_neg; int /*<<< orphan*/  wfd_ie_prov_disc_resp; int /*<<< orphan*/  wfd_ie_prov_disc_req; int /*<<< orphan*/  wfd_ie_invitation; int /*<<< orphan*/  wfd_ie_assoc_req; int /*<<< orphan*/  wfd_ie_probe_resp; int /*<<< orphan*/  wfd_ie_probe_req; int /*<<< orphan*/  wfd_ie_beacon; } ;
struct TYPE_3__ {struct p2p_data* pref_chan; struct p2p_data* serial_number; struct p2p_data* model_number; struct p2p_data* model_name; struct p2p_data* manufacturer; struct p2p_data* dev_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_flush (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_free_req_dev_types (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_go_neg_start ; 
 int /*<<< orphan*/  p2p_go_neg_wait_timeout ; 
 int /*<<< orphan*/  p2p_remove_wps_vendor_extensions (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_scan_timeout ; 
 int /*<<< orphan*/  p2p_service_flush_asp (struct p2p_data*) ; 
 int /*<<< orphan*/  p2ps_prov_free (struct p2p_data*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void p2p_deinit(struct p2p_data *p2p)
{
#ifdef CONFIG_WIFI_DISPLAY
	wpabuf_free(p2p->wfd_ie_beacon);
	wpabuf_free(p2p->wfd_ie_probe_req);
	wpabuf_free(p2p->wfd_ie_probe_resp);
	wpabuf_free(p2p->wfd_ie_assoc_req);
	wpabuf_free(p2p->wfd_ie_invitation);
	wpabuf_free(p2p->wfd_ie_prov_disc_req);
	wpabuf_free(p2p->wfd_ie_prov_disc_resp);
	wpabuf_free(p2p->wfd_ie_go_neg);
	wpabuf_free(p2p->wfd_dev_info);
	wpabuf_free(p2p->wfd_assoc_bssid);
	wpabuf_free(p2p->wfd_coupled_sink_info);
	wpabuf_free(p2p->wfd_r2_dev_info);
#endif /* CONFIG_WIFI_DISPLAY */

	eloop_cancel_timeout(p2p_scan_timeout, p2p, NULL);
	eloop_cancel_timeout(p2p_go_neg_start, p2p, NULL);
	eloop_cancel_timeout(p2p_go_neg_wait_timeout, p2p, NULL);
	p2p_flush(p2p);
	p2p_free_req_dev_types(p2p);
	os_free(p2p->cfg->dev_name);
	os_free(p2p->cfg->manufacturer);
	os_free(p2p->cfg->model_name);
	os_free(p2p->cfg->model_number);
	os_free(p2p->cfg->serial_number);
	os_free(p2p->cfg->pref_chan);
	os_free(p2p->groups);
	p2ps_prov_free(p2p);
	wpabuf_free(p2p->sd_resp);
	p2p_remove_wps_vendor_extensions(p2p);
	os_free(p2p->no_go_freq.range);
	p2p_service_flush_asp(p2p);

	os_free(p2p);
}