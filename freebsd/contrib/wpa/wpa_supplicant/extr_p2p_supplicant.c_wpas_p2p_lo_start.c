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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int p2p_lo_started; int drv_flags; TYPE_2__* conf; TYPE_1__* global; } ;
struct p2p_data {int dummy; } ;
struct TYPE_4__ {int num_sec_device_types; int /*<<< orphan*/  sec_device_type; int /*<<< orphan*/  device_type; } ;
struct TYPE_3__ {struct p2p_data* p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int WPA_DRIVER_FLAGS_P2P_LISTEN_OFFLOAD ; 
 int WPS_DEV_TYPE_LEN ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct wpabuf* p2p_build_probe_resp_template (struct p2p_data*,unsigned int) ; 
 int /*<<< orphan*/  p2p_supported_freq (struct p2p_data*,unsigned int) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int wpa_drv_p2p_lo_start (struct wpa_supplicant*,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_mhead_u8 (struct wpabuf*) ; 
 int /*<<< orphan*/  wpas_stop_listen (struct wpa_supplicant*) ; 

int wpas_p2p_lo_start(struct wpa_supplicant *wpa_s, unsigned int freq,
		      unsigned int period, unsigned int interval,
		      unsigned int count)
{
	struct p2p_data *p2p = wpa_s->global->p2p;
	u8 *device_types;
	size_t dev_types_len;
	struct wpabuf *buf;
	int ret;

	if (wpa_s->p2p_lo_started) {
		wpa_dbg(wpa_s, MSG_DEBUG,
			"P2P Listen offload is already started");
		return 0;
	}

	if (wpa_s->global->p2p == NULL ||
	    !(wpa_s->drv_flags & WPA_DRIVER_FLAGS_P2P_LISTEN_OFFLOAD)) {
		wpa_printf(MSG_DEBUG, "P2P: Listen offload not supported");
		return -1;
	}

	if (!p2p_supported_freq(wpa_s->global->p2p, freq)) {
		wpa_printf(MSG_ERROR, "P2P: Input channel not supported: %u",
			   freq);
		return -1;
	}

	/* Get device type */
	dev_types_len = (wpa_s->conf->num_sec_device_types + 1) *
		WPS_DEV_TYPE_LEN;
	device_types = os_malloc(dev_types_len);
	if (!device_types)
		return -1;
	os_memcpy(device_types, wpa_s->conf->device_type, WPS_DEV_TYPE_LEN);
	os_memcpy(&device_types[WPS_DEV_TYPE_LEN], wpa_s->conf->sec_device_type,
		  wpa_s->conf->num_sec_device_types * WPS_DEV_TYPE_LEN);

	/* Get Probe Response IE(s) */
	buf = p2p_build_probe_resp_template(p2p, freq);
	if (!buf) {
		os_free(device_types);
		return -1;
	}

	ret = wpa_drv_p2p_lo_start(wpa_s, freq, period, interval, count,
				   device_types, dev_types_len,
				   wpabuf_mhead_u8(buf), wpabuf_len(buf));
	if (ret < 0)
		wpa_dbg(wpa_s, MSG_DEBUG,
			"P2P: Failed to start P2P listen offload");

	os_free(device_types);
	wpabuf_free(buf);

	if (ret == 0) {
		wpa_s->p2p_lo_started = 1;

		/* Stop current P2P listen if any */
		wpas_stop_listen(wpa_s);
	}

	return ret;
}