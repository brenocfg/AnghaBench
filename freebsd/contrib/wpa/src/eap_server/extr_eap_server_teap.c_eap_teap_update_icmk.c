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
struct eap_teap_data {int cmk_emsk_available; scalar_t__ simck_idx; int /*<<< orphan*/  cmk_emsk; int /*<<< orphan*/  simck_emsk; int /*<<< orphan*/  cmk_msk; int /*<<< orphan*/  simck_msk; int /*<<< orphan*/  phase2_priv; TYPE_1__* phase2_method; } ;
struct eap_sm {int eap_teap_auth; } ;
struct TYPE_2__ {int /*<<< orphan*/ * (* get_emsk ) (struct eap_sm*,int /*<<< orphan*/ ,size_t*) ;int /*<<< orphan*/ * (* getKey ) (struct eap_sm*,int /*<<< orphan*/ ,size_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,size_t) ; 
 int eap_teap_derive_cmk_basic_pw_auth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int eap_teap_derive_imck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (struct eap_sm*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/ * stub2 (struct eap_sm*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_teap_update_icmk(struct eap_sm *sm, struct eap_teap_data *data)
{
	u8 *msk = NULL, *emsk = NULL;
	size_t msk_len = 0, emsk_len = 0;
	int res;

	wpa_printf(MSG_DEBUG, "EAP-TEAP: Deriving ICMK[%d] (S-IMCK and CMK)",
		   data->simck_idx + 1);

	if (sm->eap_teap_auth == 1)
		return eap_teap_derive_cmk_basic_pw_auth(data->simck_msk,
							 data->cmk_msk);

	if (!data->phase2_method || !data->phase2_priv) {
		wpa_printf(MSG_INFO, "EAP-TEAP: Phase 2 method not available");
		return -1;
	}

	if (data->phase2_method->getKey) {
		msk = data->phase2_method->getKey(sm, data->phase2_priv,
						  &msk_len);
		if (!msk) {
			wpa_printf(MSG_INFO,
				   "EAP-TEAP: Could not fetch Phase 2 MSK");
			return -1;
		}
	}

	if (data->phase2_method->get_emsk) {
		emsk = data->phase2_method->get_emsk(sm, data->phase2_priv,
						     &emsk_len);
	}

	res = eap_teap_derive_imck(data->simck_msk, data->simck_emsk,
				   msk, msk_len, emsk, emsk_len,
				   data->simck_msk, data->cmk_msk,
				   data->simck_emsk, data->cmk_emsk);
	bin_clear_free(msk, msk_len);
	bin_clear_free(emsk, emsk_len);
	if (res == 0) {
		data->simck_idx++;
		if (emsk)
			data->cmk_emsk_available = 1;
	}
	return 0;
}