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
struct hostapd_nai_realm_data {int /*<<< orphan*/ * realm; scalar_t__ encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  anqp_add_nai_realm_eap (struct wpabuf*,struct hostapd_nai_realm_data*) ; 
 int /*<<< orphan*/  gas_anqp_set_element_len (struct wpabuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ os_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,scalar_t__) ; 

__attribute__((used)) static void anqp_add_nai_realm_data(struct wpabuf *buf,
				    struct hostapd_nai_realm_data *realm,
				    unsigned int realm_idx)
{
	u8 *realm_data_len;

	wpa_printf(MSG_DEBUG, "realm=%s, len=%d", realm->realm[realm_idx],
		   (int) os_strlen(realm->realm[realm_idx]));
	realm_data_len = wpabuf_put(buf, 2);
	wpabuf_put_u8(buf, realm->encoding);
	wpabuf_put_u8(buf, os_strlen(realm->realm[realm_idx]));
	wpabuf_put_str(buf, realm->realm[realm_idx]);
	anqp_add_nai_realm_eap(buf, realm);
	gas_anqp_set_element_len(buf, realm_data_len);
}