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
struct eap_ttls_data {int /*<<< orphan*/  ssl; int /*<<< orphan*/  mschapv2_auth_response; int /*<<< orphan*/  mschapv2_ident; scalar_t__ mschapv2_resp_ok; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVP_PAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RADIUS_ATTR_MS_CHAP2_SUCCESS ; 
 int /*<<< orphan*/  RADIUS_ATTR_MS_CHAP_ERROR ; 
 int /*<<< orphan*/  RADIUS_VENDOR_ID_MICROSOFT ; 
 struct wpabuf* eap_server_tls_encrypt (struct eap_sm*,int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/ * eap_ttls_avp_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int os_snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  os_snprintf_error (int,int) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_snprintf_hex_uppercase (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct wpabuf * eap_ttls_build_phase2_mschapv2(
	struct eap_sm *sm, struct eap_ttls_data *data)
{
	struct wpabuf *encr_req, msgbuf;
	u8 *req, *pos, *end;
	int ret;

	pos = req = os_malloc(100);
	if (req == NULL)
		return NULL;
	end = req + 100;

	if (data->mschapv2_resp_ok) {
		pos = eap_ttls_avp_hdr(pos, RADIUS_ATTR_MS_CHAP2_SUCCESS,
				       RADIUS_VENDOR_ID_MICROSOFT, 1, 43);
		*pos++ = data->mschapv2_ident;
		ret = os_snprintf((char *) pos, end - pos, "S=");
		if (!os_snprintf_error(end - pos, ret))
			pos += ret;
		pos += wpa_snprintf_hex_uppercase(
			(char *) pos, end - pos, data->mschapv2_auth_response,
			sizeof(data->mschapv2_auth_response));
	} else {
		pos = eap_ttls_avp_hdr(pos, RADIUS_ATTR_MS_CHAP_ERROR,
				       RADIUS_VENDOR_ID_MICROSOFT, 1, 6);
		os_memcpy(pos, "Failed", 6);
		pos += 6;
		AVP_PAD(req, pos);
	}

	wpabuf_set(&msgbuf, req, pos - req);
	wpa_hexdump_buf_key(MSG_DEBUG, "EAP-TTLS/MSCHAPV2: Encrypting Phase 2 "
			    "data", &msgbuf);

	encr_req = eap_server_tls_encrypt(sm, &data->ssl, &msgbuf);
	os_free(req);

	return encr_req;
}