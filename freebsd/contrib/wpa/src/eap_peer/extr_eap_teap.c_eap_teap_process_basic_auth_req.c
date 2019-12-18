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
struct teap_tlv_hdr {int dummy; } ;
struct eap_teap_data {int phase2_success; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TEAP_TLV_BASIC_PASSWORD_AUTH_REQ ; 
 int /*<<< orphan*/  TEAP_TLV_BASIC_PASSWORD_AUTH_RESP ; 
 int /*<<< orphan*/ * eap_get_config_identity (struct eap_sm*,size_t*) ; 
 int /*<<< orphan*/ * eap_get_config_password (struct eap_sm*,size_t*) ; 
 int /*<<< orphan*/  eap_teap_put_tlv_hdr (struct wpabuf*,int /*<<< orphan*/ ,size_t) ; 
 struct wpabuf* eap_teap_tlv_nak (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_teap_process_basic_auth_req(
	struct eap_sm *sm, struct eap_teap_data *data,
	u8 *basic_auth_req, size_t basic_auth_req_len)
{
	const u8 *identity, *password;
	size_t identity_len, password_len, plen;
	struct wpabuf *resp;

	wpa_hexdump_ascii(MSG_DEBUG, "EAP-TEAP: Basic-Password-Auth-Req prompt",
			  basic_auth_req, basic_auth_req_len);
	/* TODO: send over control interface */

	identity = eap_get_config_identity(sm, &identity_len);
	password = eap_get_config_password(sm, &password_len);
	if (!identity || !password ||
	    identity_len > 255 || password_len > 255) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: No username/password suitable for Basic-Password-Auth");
		return eap_teap_tlv_nak(0, TEAP_TLV_BASIC_PASSWORD_AUTH_REQ);
	}

	plen = 1 + identity_len + 1 + password_len;
	resp = wpabuf_alloc(sizeof(struct teap_tlv_hdr) + plen);
	if (!resp)
		return NULL;
	eap_teap_put_tlv_hdr(resp, TEAP_TLV_BASIC_PASSWORD_AUTH_RESP, plen);
	wpabuf_put_u8(resp, identity_len);
	wpabuf_put_data(resp, identity, identity_len);
	wpabuf_put_u8(resp, password_len);
	wpabuf_put_data(resp, password, password_len);
	wpa_hexdump_buf_key(MSG_DEBUG, "EAP-TEAP: Basic-Password-Auth-Resp",
			    resp);

	/* Assume this succeeds so that Result TLV(Success) from the server can
	 * be used to terminate TEAP. */
	data->phase2_success = 1;

	return resp;
}