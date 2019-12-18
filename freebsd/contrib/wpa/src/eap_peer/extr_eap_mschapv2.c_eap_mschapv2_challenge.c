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
struct eap_sm {int dummy; } ;
struct eap_mschapv2_hdr {int /*<<< orphan*/  mschapv2_id; } ;
struct eap_mschapv2_data {int /*<<< orphan*/ * passwd_change_challenge; scalar_t__ passwd_change_challenge_valid; } ;
struct eap_method_ret {void* allowNotifications; int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; void* ignore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 void* FALSE ; 
 int /*<<< orphan*/  METHOD_MAY_CONT ; 
 size_t MSCHAPV2_CHAL_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 void* TRUE ; 
 int /*<<< orphan*/ * eap_get_config_identity (struct eap_sm*,size_t*) ; 
 int /*<<< orphan*/ * eap_get_config_password (struct eap_sm*,size_t*) ; 
 struct wpabuf* eap_mschapv2_challenge_reply (struct eap_sm*,struct eap_mschapv2_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_mschapv2_challenge(
	struct eap_sm *sm, struct eap_mschapv2_data *data,
	struct eap_method_ret *ret, const struct eap_mschapv2_hdr *req,
	size_t req_len, u8 id)
{
	size_t len, challenge_len;
	const u8 *pos, *challenge;

	if (eap_get_config_identity(sm, &len) == NULL ||
	    eap_get_config_password(sm, &len) == NULL)
		return NULL;

	wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: Received challenge");
	if (req_len < sizeof(*req) + 1) {
		wpa_printf(MSG_INFO, "EAP-MSCHAPV2: Too short challenge data "
			   "(len %lu)", (unsigned long) req_len);
		ret->ignore = TRUE;
		return NULL;
	}
	pos = (const u8 *) (req + 1);
	challenge_len = *pos++;
	len = req_len - sizeof(*req) - 1;
	if (challenge_len != MSCHAPV2_CHAL_LEN) {
		wpa_printf(MSG_INFO, "EAP-MSCHAPV2: Invalid challenge length "
			   "%lu", (unsigned long) challenge_len);
		ret->ignore = TRUE;
		return NULL;
	}

	if (len < challenge_len) {
		wpa_printf(MSG_INFO, "EAP-MSCHAPV2: Too short challenge"
			   " packet: len=%lu challenge_len=%lu",
			   (unsigned long) len, (unsigned long) challenge_len);
		ret->ignore = TRUE;
		return NULL;
	}

	if (data->passwd_change_challenge_valid) {
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: Using challenge from the "
			   "failure message");
		challenge = data->passwd_change_challenge;
	} else
		challenge = pos;
	pos += challenge_len;
	len -= challenge_len;
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-MSCHAPV2: Authentication Servername",
		    pos, len);

	ret->ignore = FALSE;
	ret->methodState = METHOD_MAY_CONT;
	ret->decision = DECISION_FAIL;
	ret->allowNotifications = TRUE;

	return eap_mschapv2_challenge_reply(sm, data, id, req->mschapv2_id,
					    challenge);
}