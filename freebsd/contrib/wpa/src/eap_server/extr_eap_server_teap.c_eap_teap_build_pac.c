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
struct teap_tlv_result {int /*<<< orphan*/  status; int /*<<< orphan*/  length; int /*<<< orphan*/  tlv_type; } ;
struct teap_tlv_hdr {void* length; void* tlv_type; } ;
struct pac_attr_hdr {void* len; void* type; } ;
struct os_time {scalar_t__ sec; } ;
struct eap_teap_data {int srv_id_len; int /*<<< orphan*/ * srv_id_info; int /*<<< orphan*/ * srv_id; scalar_t__ pac_key_lifetime; int /*<<< orphan*/  pac_opaque_encr; } ;
struct eap_sm {int identity_len; int /*<<< orphan*/ * identity; } ;

/* Variables and functions */
 int EAP_TEAP_PAC_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PAC_OPAQUE_TYPE_IDENTITY ; 
 int /*<<< orphan*/  PAC_OPAQUE_TYPE_KEY ; 
 int /*<<< orphan*/  PAC_OPAQUE_TYPE_LIFETIME ; 
 int /*<<< orphan*/  PAC_OPAQUE_TYPE_PAD ; 
 int /*<<< orphan*/  PAC_TYPE_A_ID ; 
 int /*<<< orphan*/  PAC_TYPE_A_ID_INFO ; 
 int /*<<< orphan*/  PAC_TYPE_CRED_LIFETIME ; 
 int /*<<< orphan*/  PAC_TYPE_I_ID ; 
 int PAC_TYPE_PAC_INFO ; 
 int /*<<< orphan*/  PAC_TYPE_PAC_KEY ; 
 int /*<<< orphan*/  PAC_TYPE_PAC_OPAQUE ; 
 int /*<<< orphan*/  PAC_TYPE_PAC_TYPE ; 
 int /*<<< orphan*/  PAC_TYPE_TUNNEL_PAC ; 
 int TEAP_STATUS_SUCCESS ; 
 int TEAP_TLV_MANDATORY ; 
 int TEAP_TLV_PAC ; 
 int TEAP_TLV_RESULT ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ aes_wrap (int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_teap_put_tlv (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  eap_teap_put_tlv_hdr (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 void* host_to_be16 (int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ os_get_time (struct os_time*) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t os_strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 void* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,scalar_t__) ; 

__attribute__((used)) static struct wpabuf * eap_teap_build_pac(struct eap_sm *sm,
					  struct eap_teap_data *data)
{
	u8 pac_key[EAP_TEAP_PAC_KEY_LEN];
	u8 *pac_buf, *pac_opaque;
	struct wpabuf *buf;
	u8 *pos;
	size_t buf_len, srv_id_info_len, pac_len;
	struct teap_tlv_hdr *pac_tlv;
	struct pac_attr_hdr *pac_info;
	struct teap_tlv_result *result;
	struct os_time now;

	wpa_printf(MSG_DEBUG, "EAP-TEAP: Build a new PAC");

	if (random_get_bytes(pac_key, EAP_TEAP_PAC_KEY_LEN) < 0 ||
	    os_get_time(&now) < 0)
		return NULL;
	wpa_hexdump_key(MSG_DEBUG, "EAP-TEAP: Generated PAC-Key",
			pac_key, EAP_TEAP_PAC_KEY_LEN);

	pac_len = (2 + EAP_TEAP_PAC_KEY_LEN) + (2 + 4) +
		(2 + sm->identity_len) + 8;
	pac_buf = os_malloc(pac_len);
	if (!pac_buf)
		return NULL;

	srv_id_info_len = os_strlen(data->srv_id_info);

	pos = pac_buf;
	*pos++ = PAC_OPAQUE_TYPE_KEY;
	*pos++ = EAP_TEAP_PAC_KEY_LEN;
	os_memcpy(pos, pac_key, EAP_TEAP_PAC_KEY_LEN);
	pos += EAP_TEAP_PAC_KEY_LEN;

	wpa_printf(MSG_DEBUG, "EAP-TEAP: PAC-Key lifetime: %u seconds",
		   data->pac_key_lifetime);
	*pos++ = PAC_OPAQUE_TYPE_LIFETIME;
	*pos++ = 4;
	WPA_PUT_BE32(pos, now.sec + data->pac_key_lifetime);
	pos += 4;

	if (sm->identity) {
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-TEAP: PAC-Opaque Identity",
				  sm->identity, sm->identity_len);
		*pos++ = PAC_OPAQUE_TYPE_IDENTITY;
		*pos++ = sm->identity_len;
		os_memcpy(pos, sm->identity, sm->identity_len);
		pos += sm->identity_len;
	}

	pac_len = pos - pac_buf;
	while (pac_len % 8) {
		*pos++ = PAC_OPAQUE_TYPE_PAD;
		pac_len++;
	}

	pac_opaque = os_malloc(pac_len + 8);
	if (!pac_opaque) {
		os_free(pac_buf);
		return NULL;
	}
	if (aes_wrap(data->pac_opaque_encr, sizeof(data->pac_opaque_encr),
		     pac_len / 8, pac_buf, pac_opaque) < 0) {
		os_free(pac_buf);
		os_free(pac_opaque);
		return NULL;
	}
	os_free(pac_buf);

	pac_len += 8;
	wpa_hexdump(MSG_DEBUG, "EAP-TEAP: PAC-Opaque", pac_opaque, pac_len);

	buf_len = sizeof(*pac_tlv) +
		sizeof(struct pac_attr_hdr) + EAP_TEAP_PAC_KEY_LEN +
		sizeof(struct pac_attr_hdr) + pac_len +
		data->srv_id_len + srv_id_info_len + 100 + sizeof(*result);
	buf = wpabuf_alloc(buf_len);
	if (!buf) {
		os_free(pac_opaque);
		return NULL;
	}

	/* Result TLV */
	wpa_printf(MSG_DEBUG, "EAP-TEAP: Add Result TLV (status=SUCCESS)");
	result = wpabuf_put(buf, sizeof(*result));
	WPA_PUT_BE16((u8 *) &result->tlv_type,
		     TEAP_TLV_MANDATORY | TEAP_TLV_RESULT);
	WPA_PUT_BE16((u8 *) &result->length, 2);
	WPA_PUT_BE16((u8 *) &result->status, TEAP_STATUS_SUCCESS);

	/* PAC TLV */
	wpa_printf(MSG_DEBUG, "EAP-TEAP: Add PAC TLV");
	pac_tlv = wpabuf_put(buf, sizeof(*pac_tlv));
	pac_tlv->tlv_type = host_to_be16(TEAP_TLV_MANDATORY | TEAP_TLV_PAC);

	/* PAC-Key */
	eap_teap_put_tlv(buf, PAC_TYPE_PAC_KEY, pac_key, EAP_TEAP_PAC_KEY_LEN);

	/* PAC-Opaque */
	eap_teap_put_tlv(buf, PAC_TYPE_PAC_OPAQUE, pac_opaque, pac_len);
	os_free(pac_opaque);

	/* PAC-Info */
	pac_info = wpabuf_put(buf, sizeof(*pac_info));
	pac_info->type = host_to_be16(PAC_TYPE_PAC_INFO);

	/* PAC-Lifetime (inside PAC-Info) */
	eap_teap_put_tlv_hdr(buf, PAC_TYPE_CRED_LIFETIME, 4);
	wpabuf_put_be32(buf, now.sec + data->pac_key_lifetime);

	/* A-ID (inside PAC-Info) */
	eap_teap_put_tlv(buf, PAC_TYPE_A_ID, data->srv_id, data->srv_id_len);

	/* Note: headers may be misaligned after A-ID */

	if (sm->identity) {
		eap_teap_put_tlv(buf, PAC_TYPE_I_ID, sm->identity,
				 sm->identity_len);
	}

	/* A-ID-Info (inside PAC-Info) */
	eap_teap_put_tlv(buf, PAC_TYPE_A_ID_INFO, data->srv_id_info,
			 srv_id_info_len);

	/* PAC-Type (inside PAC-Info) */
	eap_teap_put_tlv_hdr(buf, PAC_TYPE_PAC_TYPE, 2);
	wpabuf_put_be16(buf, PAC_TYPE_TUNNEL_PAC);

	/* Update PAC-Info and PAC TLV Length fields */
	pos = wpabuf_put(buf, 0);
	pac_info->len = host_to_be16(pos - (u8 *) (pac_info + 1));
	pac_tlv->length = host_to_be16(pos - (u8 *) (pac_tlv + 1));

	return buf;
}