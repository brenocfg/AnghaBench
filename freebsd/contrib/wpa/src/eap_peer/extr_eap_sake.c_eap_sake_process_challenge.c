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
struct eap_sm {int dummy; } ;
struct eap_sake_parse_attr {int /*<<< orphan*/  serverid_len; scalar_t__ serverid; int /*<<< orphan*/  rand_s; } ;
struct TYPE_2__ {int /*<<< orphan*/  auth; } ;
struct eap_sake_data {scalar_t__ state; int peerid_len; scalar_t__ peerid; int /*<<< orphan*/  serverid_len; int /*<<< orphan*/ * serverid; scalar_t__ rand_p; scalar_t__ rand_s; TYPE_1__ tek; int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; int /*<<< orphan*/  root_secret_b; int /*<<< orphan*/  root_secret_a; } ;
struct eap_method_ret {int /*<<< orphan*/  ignore; } ;

/* Variables and functions */
 scalar_t__ CHALLENGE ; 
 scalar_t__ CONFIRM ; 
 int EAP_SAKE_AT_MIC_P ; 
 int /*<<< orphan*/  EAP_SAKE_AT_PEERID ; 
 int /*<<< orphan*/  EAP_SAKE_AT_RAND_P ; 
 int EAP_SAKE_MIC_LEN ; 
 int EAP_SAKE_RAND_LEN ; 
 int /*<<< orphan*/  EAP_SAKE_SUBTYPE_CHALLENGE ; 
 scalar_t__ IDENTITY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eap_sake_add_attr (struct wpabuf*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct wpabuf* eap_sake_build_msg (struct eap_sake_data*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sake_compute_mic (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ eap_sake_derive_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sake_parse_attributes (int /*<<< orphan*/  const*,size_t,struct eap_sake_parse_attr*) ; 
 int /*<<< orphan*/  eap_sake_state (struct eap_sake_data*,scalar_t__) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * os_memdup (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ random_get_bytes (scalar_t__,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_sake_process_challenge(struct eap_sm *sm,
						  struct eap_sake_data *data,
						  struct eap_method_ret *ret,
						  u8 id,
						  const u8 *payload,
						  size_t payload_len)
{
	struct eap_sake_parse_attr attr;
	struct wpabuf *resp;
	u8 *rpos;
	size_t rlen;

	if (data->state != IDENTITY && data->state != CHALLENGE) {
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Request/Challenge received "
			   "in unexpected state (%d)", data->state);
		ret->ignore = TRUE;
		return NULL;
	}
	if (data->state == IDENTITY)
		eap_sake_state(data, CHALLENGE);

	wpa_printf(MSG_DEBUG, "EAP-SAKE: Received Request/Challenge");

	if (eap_sake_parse_attributes(payload, payload_len, &attr))
		return NULL;

	if (!attr.rand_s) {
		wpa_printf(MSG_INFO, "EAP-SAKE: Request/Challenge did not "
			   "include AT_RAND_S");
		return NULL;
	}

	os_memcpy(data->rand_s, attr.rand_s, EAP_SAKE_RAND_LEN);
	wpa_hexdump(MSG_MSGDUMP, "EAP-SAKE: RAND_S (server rand)",
		    data->rand_s, EAP_SAKE_RAND_LEN);

	if (random_get_bytes(data->rand_p, EAP_SAKE_RAND_LEN)) {
		wpa_printf(MSG_ERROR, "EAP-SAKE: Failed to get random data");
		return NULL;
	}
	wpa_hexdump(MSG_MSGDUMP, "EAP-SAKE: RAND_P (peer rand)",
		    data->rand_p, EAP_SAKE_RAND_LEN);

	os_free(data->serverid);
	data->serverid = NULL;
	data->serverid_len = 0;
	if (attr.serverid) {
		wpa_hexdump_ascii(MSG_MSGDUMP, "EAP-SAKE: SERVERID",
				  attr.serverid, attr.serverid_len);
		data->serverid = os_memdup(attr.serverid, attr.serverid_len);
		if (data->serverid == NULL)
			return NULL;
		data->serverid_len = attr.serverid_len;
	}

	if (eap_sake_derive_keys(data->root_secret_a, data->root_secret_b,
				 data->rand_s, data->rand_p,
				 (u8 *) &data->tek, data->msk,
				 data->emsk) < 0) {
		wpa_printf(MSG_INFO, "EAP-SAKE: Failed to derive keys");
		return NULL;
	}

	wpa_printf(MSG_DEBUG, "EAP-SAKE: Sending Response/Challenge");

	rlen = 2 + EAP_SAKE_RAND_LEN + 2 + EAP_SAKE_MIC_LEN;
	if (data->peerid)
		rlen += 2 + data->peerid_len;
	resp = eap_sake_build_msg(data, id, rlen, EAP_SAKE_SUBTYPE_CHALLENGE);
	if (resp == NULL)
		return NULL;

	wpa_printf(MSG_DEBUG, "EAP-SAKE: * AT_RAND_P");
	eap_sake_add_attr(resp, EAP_SAKE_AT_RAND_P,
			  data->rand_p, EAP_SAKE_RAND_LEN);

	if (data->peerid) {
		wpa_printf(MSG_DEBUG, "EAP-SAKE: * AT_PEERID");
		eap_sake_add_attr(resp, EAP_SAKE_AT_PEERID,
				  data->peerid, data->peerid_len);
	}

	wpa_printf(MSG_DEBUG, "EAP-SAKE: * AT_MIC_P");
	wpabuf_put_u8(resp, EAP_SAKE_AT_MIC_P);
	wpabuf_put_u8(resp, 2 + EAP_SAKE_MIC_LEN);
	rpos = wpabuf_put(resp, EAP_SAKE_MIC_LEN);
	if (eap_sake_compute_mic(data->tek.auth, data->rand_s, data->rand_p,
				 data->serverid, data->serverid_len,
				 data->peerid, data->peerid_len, 1,
				 wpabuf_head(resp), wpabuf_len(resp), rpos,
				 rpos)) {
		wpa_printf(MSG_INFO, "EAP-SAKE: Failed to compute MIC");
		wpabuf_free(resp);
		return NULL;
	}

	eap_sake_state(data, CONFIRM);

	return resp;
}