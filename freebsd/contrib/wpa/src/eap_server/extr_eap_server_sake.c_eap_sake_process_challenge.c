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
struct eap_sm {int /*<<< orphan*/  server_id_len; int /*<<< orphan*/  server_id; TYPE_1__* user; } ;
struct eap_sake_parse_attr {int /*<<< orphan*/  mic_p; int /*<<< orphan*/  peerid_len; scalar_t__ peerid; int /*<<< orphan*/  rand_p; } ;
struct TYPE_4__ {int /*<<< orphan*/  auth; } ;
struct eap_sake_data {scalar_t__ state; int /*<<< orphan*/  peerid_len; int /*<<< orphan*/ * peerid; int /*<<< orphan*/  rand_p; int /*<<< orphan*/  rand_s; TYPE_2__ tek; int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; } ;
struct TYPE_3__ {int password_len; int /*<<< orphan*/ * password; } ;

/* Variables and functions */
 scalar_t__ CHALLENGE ; 
 void* CONFIRM ; 
 int EAP_SAKE_MIC_LEN ; 
 int /*<<< orphan*/  EAP_SAKE_RAND_LEN ; 
 int EAP_SAKE_ROOT_SECRET_LEN ; 
 void* FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ eap_sake_compute_mic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ eap_sake_derive_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sake_parse_attributes (int /*<<< orphan*/  const*,size_t,struct eap_sake_parse_attr*) ; 
 int /*<<< orphan*/  eap_sake_state (struct eap_sake_data*,void*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_memdup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static void eap_sake_process_challenge(struct eap_sm *sm,
				       struct eap_sake_data *data,
				       const struct wpabuf *respData,
				       const u8 *payload, size_t payloadlen)
{
	struct eap_sake_parse_attr attr;
	u8 mic_p[EAP_SAKE_MIC_LEN];

	if (data->state != CHALLENGE)
		return;

	wpa_printf(MSG_DEBUG, "EAP-SAKE: Received Response/Challenge");

	if (eap_sake_parse_attributes(payload, payloadlen, &attr))
		return;

	if (!attr.rand_p || !attr.mic_p) {
		wpa_printf(MSG_INFO, "EAP-SAKE: Response/Challenge did not "
			   "include AT_RAND_P or AT_MIC_P");
		return;
	}

	os_memcpy(data->rand_p, attr.rand_p, EAP_SAKE_RAND_LEN);

	os_free(data->peerid);
	data->peerid = NULL;
	data->peerid_len = 0;
	if (attr.peerid) {
		data->peerid = os_memdup(attr.peerid, attr.peerid_len);
		if (data->peerid == NULL)
			return;
		data->peerid_len = attr.peerid_len;
	}

	if (sm->user == NULL || sm->user->password == NULL ||
	    sm->user->password_len != 2 * EAP_SAKE_ROOT_SECRET_LEN) {
		wpa_printf(MSG_INFO, "EAP-SAKE: Plaintext password with "
			   "%d-byte key not configured",
			   2 * EAP_SAKE_ROOT_SECRET_LEN);
		data->state = FAILURE;
		return;
	}
	if (eap_sake_derive_keys(sm->user->password,
				 sm->user->password + EAP_SAKE_ROOT_SECRET_LEN,
				 data->rand_s, data->rand_p,
				 (u8 *) &data->tek, data->msk,
				 data->emsk) < 0) {
		wpa_printf(MSG_INFO, "EAP-SAKE: Failed to derive keys");
		data->state = FAILURE;
		return;
	}

	if (eap_sake_compute_mic(data->tek.auth, data->rand_s, data->rand_p,
				 sm->server_id, sm->server_id_len,
				 data->peerid, data->peerid_len, 1,
				 wpabuf_head(respData), wpabuf_len(respData),
				 attr.mic_p, mic_p) < 0) {
		wpa_printf(MSG_INFO, "EAP-SAKE: Failed to compute MIC");
		data->state = FAILURE;
		return;
	}
	if (os_memcmp_const(attr.mic_p, mic_p, EAP_SAKE_MIC_LEN) != 0) {
		wpa_printf(MSG_INFO, "EAP-SAKE: Incorrect AT_MIC_P");
		eap_sake_state(data, FAILURE);
		return;
	}

	eap_sake_state(data, CONFIRM);
}