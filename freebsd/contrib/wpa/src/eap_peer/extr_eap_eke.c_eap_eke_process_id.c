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
typedef  scalar_t__ u8 ;
typedef  struct wpabuf const wpabuf ;
struct eap_method_ret {int dummy; } ;
struct eap_eke_data {scalar_t__ state; scalar_t__ const dhgroup; scalar_t__ const encr; scalar_t__ const prf; scalar_t__ const mac; int serverid_len; int peerid_len; scalar_t__ const* peerid; struct wpabuf const* msgs; int /*<<< orphan*/ * serverid; int /*<<< orphan*/  sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_NO_PROPOSAL_CHOSEN ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EAP_EKE_FAIL_PROTO_ERROR ; 
 int /*<<< orphan*/  EAP_EKE_ID ; 
 int EAP_EKE_ID_NAI ; 
 scalar_t__ IDENTITY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf const* eap_eke_build_fail (struct eap_eke_data*,struct eap_method_ret*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct wpabuf const* eap_eke_build_msg (struct eap_eke_data*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_eke_session_init (int /*<<< orphan*/ *,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const) ; 
 int /*<<< orphan*/  eap_eke_state (struct eap_eke_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_eke_supp_dhgroup (scalar_t__ const) ; 
 int /*<<< orphan*/  eap_eke_supp_encr (scalar_t__ const) ; 
 int /*<<< orphan*/  eap_eke_supp_mac (scalar_t__ const) ; 
 int /*<<< orphan*/  eap_eke_supp_prf (scalar_t__ const) ; 
 scalar_t__ eap_get_id (struct wpabuf const*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_memdup (scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf const* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf const*) ; 
 scalar_t__ wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf const*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf const*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf const*,int) ; 

__attribute__((used)) static struct wpabuf * eap_eke_process_id(struct eap_eke_data *data,
					  struct eap_method_ret *ret,
					  const struct wpabuf *reqData,
					  const u8 *payload,
					  size_t payload_len)
{
	struct wpabuf *resp;
	unsigned num_prop, i;
	const u8 *pos, *end;
	const u8 *prop = NULL;
	u8 idtype;
	u8 id = eap_get_id(reqData);

	if (data->state != IDENTITY) {
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PROTO_ERROR);
	}

	wpa_printf(MSG_DEBUG, "EAP-EKE: Received EAP-EKE-ID/Request");

	if (payload_len < 2 + 4) {
		wpa_printf(MSG_DEBUG, "EAP-EKE: Too short ID/Request Data");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PROTO_ERROR);
	}

	pos = payload;
	end = payload + payload_len;

	num_prop = *pos++;
	pos++; /* Ignore Reserved field */

	if (pos + num_prop * 4 > end) {
		wpa_printf(MSG_DEBUG, "EAP-EKE: Too short ID/Request Data (num_prop=%u)",
			   num_prop);
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PROTO_ERROR);
	}

	for (i = 0; i < num_prop; i++) {
		const u8 *tmp = pos;

		wpa_printf(MSG_DEBUG, "EAP-EKE: Proposal #%u: dh=%u encr=%u prf=%u mac=%u",
			   i, pos[0], pos[1], pos[2], pos[3]);
		pos += 4;

		if ((data->dhgroup && data->dhgroup != *tmp) ||
		    !eap_eke_supp_dhgroup(*tmp))
			continue;
		tmp++;
		if ((data->encr && data->encr != *tmp) ||
		    !eap_eke_supp_encr(*tmp))
			continue;
		tmp++;
		if ((data->prf && data->prf != *tmp) ||
		    !eap_eke_supp_prf(*tmp))
			continue;
		tmp++;
		if ((data->mac && data->mac != *tmp) ||
		    !eap_eke_supp_mac(*tmp))
			continue;

		prop = tmp - 3;
		if (eap_eke_session_init(&data->sess, prop[0], prop[1], prop[2],
					 prop[3]) < 0) {
			prop = NULL;
			continue;
		}

		wpa_printf(MSG_DEBUG, "EAP-EKE: Selected proposal");
		break;
	}

	if (prop == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-EKE: No acceptable proposal found");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_NO_PROPOSAL_CHOSEN);
	}

	pos += (num_prop - i - 1) * 4;

	if (pos == end) {
		wpa_printf(MSG_DEBUG, "EAP-EKE: Too short ID/Request Data to include IDType/Identity");
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PROTO_ERROR);
	}

	idtype = *pos++;
	wpa_printf(MSG_DEBUG, "EAP-EKE: Server IDType %u", idtype);
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-EKE: Server Identity",
			  pos, end - pos);
	os_free(data->serverid);
	data->serverid = os_memdup(pos, end - pos);
	if (data->serverid == NULL) {
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}
	data->serverid_len = end - pos;

	wpa_printf(MSG_DEBUG, "EAP-EKE: Sending EAP-EKE-ID/Response");

	resp = eap_eke_build_msg(data, id,
				 2 + 4 + 1 + data->peerid_len,
				 EAP_EKE_ID);
	if (resp == NULL) {
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}

	wpabuf_put_u8(resp, 1); /* NumProposals */
	wpabuf_put_u8(resp, 0); /* Reserved */
	wpabuf_put_data(resp, prop, 4); /* Selected Proposal */
	wpabuf_put_u8(resp, EAP_EKE_ID_NAI);
	if (data->peerid)
		wpabuf_put_data(resp, data->peerid, data->peerid_len);

	wpabuf_free(data->msgs);
	data->msgs = wpabuf_alloc(wpabuf_len(reqData) + wpabuf_len(resp));
	if (data->msgs == NULL) {
		wpabuf_free(resp);
		return eap_eke_build_fail(data, ret, id,
					  EAP_EKE_FAIL_PRIVATE_INTERNAL_ERROR);
	}
	wpabuf_put_buf(data->msgs, reqData);
	wpabuf_put_buf(data->msgs, resp);

	eap_eke_state(data, COMMIT);

	return resp;
}