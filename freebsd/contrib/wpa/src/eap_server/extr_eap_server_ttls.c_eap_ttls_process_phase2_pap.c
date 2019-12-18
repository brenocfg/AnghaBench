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
struct eap_ttls_data {int dummy; } ;
struct eap_sm {TYPE_1__* user; } ;
struct TYPE_2__ {int ttls_auth; size_t password_len; int /*<<< orphan*/  password; scalar_t__ password_hash; } ;

/* Variables and functions */
 int EAP_TTLS_AUTH_PAP ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  eap_ttls_state (struct eap_ttls_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_ttls_valid_session (struct eap_sm*,struct eap_ttls_data*) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_ttls_process_phase2_pap(struct eap_sm *sm,
					struct eap_ttls_data *data,
					const u8 *user_password,
					size_t user_password_len)
{
	if (!sm->user || !sm->user->password || sm->user->password_hash ||
	    !(sm->user->ttls_auth & EAP_TTLS_AUTH_PAP)) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/PAP: No plaintext user "
			   "password configured");
		eap_ttls_state(data, FAILURE);
		return;
	}

	if (sm->user->password_len != user_password_len ||
	    os_memcmp_const(sm->user->password, user_password,
			    user_password_len) != 0) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/PAP: Invalid user password");
		eap_ttls_state(data, FAILURE);
		return;
	}

	wpa_printf(MSG_DEBUG, "EAP-TTLS/PAP: Correct user password");
	eap_ttls_state(data, SUCCESS);
	eap_ttls_valid_session(sm, data);
}