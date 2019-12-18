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
struct radius_ms_mppe_keys {scalar_t__ send_len; scalar_t__ recv_len; struct radius_ms_mppe_keys* recv; struct radius_ms_mppe_keys* send; } ;
typedef  struct radius_ms_mppe_keys u8 ;
struct radius_msg {int dummy; } ;
struct eapol_test_data {size_t authenticator_pmk_len; int authenticator_pmk; int authenticator_eap_key_name; size_t authenticator_eap_key_name_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ PMK_LEN ; 
 int /*<<< orphan*/  RADIUS_ATTR_EAP_KEY_NAME ; 
 int /*<<< orphan*/  os_free (struct radius_ms_mppe_keys*) ; 
 int /*<<< orphan*/  os_memcpy (int,struct radius_ms_mppe_keys*,size_t) ; 
 scalar_t__ radius_msg_get_attr_ptr (struct radius_msg*,int /*<<< orphan*/ ,struct radius_ms_mppe_keys**,size_t*,int /*<<< orphan*/ *) ; 
 struct radius_ms_mppe_keys* radius_msg_get_cisco_keys (struct radius_msg*,struct radius_msg*,struct radius_ms_mppe_keys const*,size_t) ; 
 struct radius_ms_mppe_keys* radius_msg_get_ms_keys (struct radius_msg*,struct radius_msg*,struct radius_ms_mppe_keys const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,struct radius_ms_mppe_keys*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ieee802_1x_get_keys(struct eapol_test_data *e,
				struct radius_msg *msg, struct radius_msg *req,
				const u8 *shared_secret,
				size_t shared_secret_len)
{
	struct radius_ms_mppe_keys *keys;
	u8 *buf;
	size_t len;

	keys = radius_msg_get_ms_keys(msg, req, shared_secret,
				      shared_secret_len);
	if (keys && keys->send == NULL && keys->recv == NULL) {
		os_free(keys);
		keys = radius_msg_get_cisco_keys(msg, req, shared_secret,
						 shared_secret_len);
	}

	if (keys) {
		if (keys->send) {
			wpa_hexdump(MSG_DEBUG, "MS-MPPE-Send-Key (sign)",
				    keys->send, keys->send_len);
		}
		if (keys->recv) {
			wpa_hexdump(MSG_DEBUG, "MS-MPPE-Recv-Key (crypt)",
				    keys->recv, keys->recv_len);
			e->authenticator_pmk_len =
				keys->recv_len > PMK_LEN ? PMK_LEN :
				keys->recv_len;
			os_memcpy(e->authenticator_pmk, keys->recv,
				  e->authenticator_pmk_len);
			if (e->authenticator_pmk_len == 16 && keys->send &&
			    keys->send_len == 16) {
				/* MS-CHAP-v2 derives 16 octet keys */
				wpa_printf(MSG_DEBUG, "Use MS-MPPE-Send-Key "
					   "to extend PMK to 32 octets");
				os_memcpy(e->authenticator_pmk +
					  e->authenticator_pmk_len,
					  keys->send, keys->send_len);
				e->authenticator_pmk_len += keys->send_len;
			}
		}

		os_free(keys->send);
		os_free(keys->recv);
		os_free(keys);
	}

	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_EAP_KEY_NAME, &buf, &len,
				    NULL) == 0) {
		os_memcpy(e->authenticator_eap_key_name, buf, len);
		e->authenticator_eap_key_name_len = len;
	} else {
		e->authenticator_eap_key_name_len = 0;
	}
}