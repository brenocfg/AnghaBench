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
typedef  int u8 ;
struct eap_teap_data {int dummy; } ;
struct eap_sm {int* identity; int identity_len; TYPE_1__* user; } ;
struct TYPE_2__ {int password_len; int /*<<< orphan*/  password; scalar_t__ password_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_BINDING ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_teap_req_failure (struct eap_teap_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_teap_state (struct eap_teap_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_teap_update_icmk (struct eap_sm*,struct eap_teap_data*) ; 
 scalar_t__ eap_user_get (struct eap_sm*,int*,int,int) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ ,int*,int) ; 
 int* os_memdup (int*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_teap_process_basic_auth_resp(struct eap_sm *sm,
					     struct eap_teap_data *data,
					     u8 *in_data, size_t in_len)
{
	u8 *pos, *end, *username, *password, *new_id;
	u8 userlen, passlen;

	pos = in_data;
	end = pos + in_len;

	if (end - pos < 1) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: No room for Basic-Password-Auth-Resp Userlen field");
		eap_teap_req_failure(data, 0);
		return;
	}
	userlen = *pos++;
	if (end - pos < userlen) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Truncated Basic-Password-Auth-Resp Username field");
		eap_teap_req_failure(data, 0);
		return;
	}
	username = pos;
	pos += userlen;
	wpa_hexdump_ascii(MSG_DEBUG,
			  "EAP-TEAP: Basic-Password-Auth-Resp Username",
			  username, userlen);

	if (end - pos < 1) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: No room for Basic-Password-Auth-Resp Passlen field");
		eap_teap_req_failure(data, 0);
		return;
	}
	passlen = *pos++;
	if (end - pos < passlen) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Truncated Basic-Password-Auth-Resp Password field");
		eap_teap_req_failure(data, 0);
		return;
	}
	password = pos;
	pos += passlen;
	wpa_hexdump_ascii_key(MSG_DEBUG,
			      "EAP-TEAP: Basic-Password-Auth-Resp Password",
			      password, passlen);

	if (end > pos) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Unexpected %d extra octet(s) at the end of Basic-Password-Auth-Resp TLV",
			   (int) (end - pos));
		eap_teap_req_failure(data, 0);
		return;
	}

	if (eap_user_get(sm, username, userlen, 1) != 0) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Username not found in the user database");
		eap_teap_req_failure(data, 0);
		return;
	}

	if (!sm->user || !sm->user->password || sm->user->password_hash) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: No plaintext user password configured");
		eap_teap_req_failure(data, 0);
		return;
	}

	if (sm->user->password_len != passlen ||
	    os_memcmp_const(sm->user->password, password, passlen) != 0) {
		wpa_printf(MSG_DEBUG, "EAP-TEAP: Invalid password");
		eap_teap_req_failure(data, 0);
		return;
	}

	wpa_printf(MSG_DEBUG, "EAP-TEAP: Correct password");
	new_id = os_memdup(username, userlen);
	if (new_id) {
		os_free(sm->identity);
		sm->identity = new_id;
		sm->identity_len = userlen;
	}
	eap_teap_state(data, CRYPTO_BINDING);
	eap_teap_update_icmk(sm, data);
}