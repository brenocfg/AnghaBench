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
struct eap_teap_data {int srv_id_len; int teap_version; int /*<<< orphan*/  server_outer_tlvs; int /*<<< orphan*/  srv_id; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int EAP_TEAP_FLAGS_OUTER_TLV_LEN ; 
 int EAP_TLS_FLAGS_START ; 
 int /*<<< orphan*/  EAP_TYPE_TEAP ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  PHASE1 ; 
 int /*<<< orphan*/  TEAP_TLV_AUTHORITY_ID ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_teap_put_tlv (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eap_teap_state (struct eap_teap_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_alloc_copy (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_teap_build_start(struct eap_sm *sm,
					    struct eap_teap_data *data, u8 id)
{
	struct wpabuf *req;
	size_t outer_tlv_len = sizeof(struct teap_tlv_hdr) + data->srv_id_len;
	const u8 *start, *end;

	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_TEAP,
			    1 + 4 + outer_tlv_len, EAP_CODE_REQUEST, id);
	if (!req) {
		wpa_printf(MSG_ERROR,
			   "EAP-TEAP: Failed to allocate memory for request");
		eap_teap_state(data, FAILURE);
		return NULL;
	}

	wpabuf_put_u8(req, EAP_TLS_FLAGS_START | EAP_TEAP_FLAGS_OUTER_TLV_LEN |
		      data->teap_version);
	wpabuf_put_be32(req, outer_tlv_len);

	start = wpabuf_put(req, 0);

	/* RFC 7170, Section 4.2.2: Authority-ID TLV */
	eap_teap_put_tlv(req, TEAP_TLV_AUTHORITY_ID,
			 data->srv_id, data->srv_id_len);

	end = wpabuf_put(req, 0);
	wpabuf_free(data->server_outer_tlvs);
	data->server_outer_tlvs = wpabuf_alloc_copy(start, end - start);
	if (!data->server_outer_tlvs) {
		eap_teap_state(data, FAILURE);
		return NULL;
	}

	eap_teap_state(data, PHASE1);

	return req;
}