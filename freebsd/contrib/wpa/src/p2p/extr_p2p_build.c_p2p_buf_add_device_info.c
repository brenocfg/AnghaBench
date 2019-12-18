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
typedef  size_t u16 ;
struct wpabuf {int dummy; } ;
struct p2p_device {scalar_t__ wps_method; } ;
struct p2p_data {TYPE_1__* cfg; } ;
struct TYPE_2__ {int config_methods; size_t num_sec_dev_types; scalar_t__ dev_name; scalar_t__* sec_dev_type; scalar_t__ pri_dev_type; scalar_t__ dev_addr; } ;

/* Variables and functions */
 size_t ATTR_DEV_NAME ; 
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t P2P_ATTR_DEVICE_INFO ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (int /*<<< orphan*/ *,int) ; 
 size_t WPS_CONFIG_DISPLAY ; 
 size_t WPS_CONFIG_KEYPAD ; 
 size_t WPS_CONFIG_P2PS ; 
 size_t WPS_CONFIG_PUSHBUTTON ; 
 size_t WPS_DEV_TYPE_LEN ; 
 scalar_t__ WPS_NOT_READY ; 
 scalar_t__ WPS_P2PS ; 
 scalar_t__ WPS_PBC ; 
 scalar_t__ WPS_PIN_DISPLAY ; 
 scalar_t__ WPS_PIN_KEYPAD ; 
 size_t os_strlen (scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,size_t) ; 

void p2p_buf_add_device_info(struct wpabuf *buf, struct p2p_data *p2p,
			     struct p2p_device *peer)
{
	u8 *len;
	u16 methods;
	size_t nlen, i;

	/* P2P Device Info */
	wpabuf_put_u8(buf, P2P_ATTR_DEVICE_INFO);
	len = wpabuf_put(buf, 2); /* IE length to be filled */

	/* P2P Device address */
	wpabuf_put_data(buf, p2p->cfg->dev_addr, ETH_ALEN);

	/* Config Methods */
	methods = 0;
	if (peer && peer->wps_method != WPS_NOT_READY) {
		if (peer->wps_method == WPS_PBC)
			methods |= WPS_CONFIG_PUSHBUTTON;
		else if (peer->wps_method == WPS_P2PS)
			methods |= WPS_CONFIG_P2PS;
		else if (peer->wps_method == WPS_PIN_DISPLAY ||
			 peer->wps_method == WPS_PIN_KEYPAD)
			methods |= WPS_CONFIG_DISPLAY | WPS_CONFIG_KEYPAD;
	} else if (p2p->cfg->config_methods) {
		methods |= p2p->cfg->config_methods &
			(WPS_CONFIG_PUSHBUTTON | WPS_CONFIG_DISPLAY |
			 WPS_CONFIG_KEYPAD | WPS_CONFIG_P2PS);
	} else {
		methods |= WPS_CONFIG_PUSHBUTTON;
		methods |= WPS_CONFIG_DISPLAY | WPS_CONFIG_KEYPAD;
		methods |= WPS_CONFIG_P2PS;
	}
	wpabuf_put_be16(buf, methods);

	/* Primary Device Type */
	wpabuf_put_data(buf, p2p->cfg->pri_dev_type,
			sizeof(p2p->cfg->pri_dev_type));

	/* Number of Secondary Device Types */
	wpabuf_put_u8(buf, p2p->cfg->num_sec_dev_types);

	/* Secondary Device Type List */
	for (i = 0; i < p2p->cfg->num_sec_dev_types; i++)
		wpabuf_put_data(buf, p2p->cfg->sec_dev_type[i],
				WPS_DEV_TYPE_LEN);

	/* Device Name */
	nlen = p2p->cfg->dev_name ? os_strlen(p2p->cfg->dev_name) : 0;
	wpabuf_put_be16(buf, ATTR_DEV_NAME);
	wpabuf_put_be16(buf, nlen);
	wpabuf_put_data(buf, p2p->cfg->dev_name, nlen);

	/* Update attribute length */
	WPA_PUT_LE16(len, (u8 *) wpabuf_put(buf, 0) - len - 2);
	wpa_printf(MSG_DEBUG, "P2P: * Device Info");
}