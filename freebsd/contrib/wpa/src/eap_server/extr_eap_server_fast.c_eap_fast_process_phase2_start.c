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
struct eap_sm {int require_identity_match; int user_eap_method_index; TYPE_2__* user; scalar_t__ identity_len; int /*<<< orphan*/ * identity; } ;
struct eap_fast_data {scalar_t__ identity_len; int /*<<< orphan*/ * identity; } ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {int /*<<< orphan*/  method; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_IDENTITY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PHASE2_ID ; 
 int /*<<< orphan*/  PHASE2_METHOD ; 
 int eap_fast_phase2_init (struct eap_sm*,struct eap_fast_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_fast_req_failure (struct eap_sm*,struct eap_fast_data*) ; 
 int /*<<< orphan*/  eap_fast_state (struct eap_fast_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_user_get (struct eap_sm*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_fast_process_phase2_start(struct eap_sm *sm,
					 struct eap_fast_data *data)
{
	u8 next_type;

	if (data->identity) {
		os_free(sm->identity);
		sm->identity = data->identity;
		data->identity = NULL;
		sm->identity_len = data->identity_len;
		data->identity_len = 0;
		sm->require_identity_match = 1;
		if (eap_user_get(sm, sm->identity, sm->identity_len, 1) != 0) {
			wpa_hexdump_ascii(MSG_DEBUG, "EAP-FAST: "
					  "Phase2 Identity not found "
					  "in the user database",
					  sm->identity, sm->identity_len);
			next_type = eap_fast_req_failure(sm, data);
		} else {
			wpa_printf(MSG_DEBUG, "EAP-FAST: Identity already "
				   "known - skip Phase 2 Identity Request");
			next_type = sm->user->methods[0].method;
			sm->user_eap_method_index = 1;
		}

		eap_fast_state(data, PHASE2_METHOD);
	} else {
		eap_fast_state(data, PHASE2_ID);
		next_type = EAP_TYPE_IDENTITY;
	}

	return eap_fast_phase2_init(sm, data, next_type);
}