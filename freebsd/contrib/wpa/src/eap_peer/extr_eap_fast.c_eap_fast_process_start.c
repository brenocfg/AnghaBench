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
typedef  int u8 ;
struct eap_sm {int dummy; } ;
struct eap_fast_data {int fast_version; int provisioning; int /*<<< orphan*/  provisioning_allowed; scalar_t__ current_pac; scalar_t__ resuming; } ;

/* Variables and functions */
 int EAP_TLS_VERSION_MASK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_fast_clear_pac_opaque_ext (struct eap_sm*,struct eap_fast_data*) ; 
 int* eap_fast_get_a_id (int const*,size_t,size_t*) ; 
 int /*<<< orphan*/  eap_fast_select_pac (struct eap_fast_data*,int const*,size_t) ; 
 scalar_t__ eap_fast_set_provisioning_ciphers (struct eap_sm*,struct eap_fast_data*) ; 
 scalar_t__ eap_fast_use_pac_opaque (struct eap_sm*,struct eap_fast_data*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_fast_process_start(struct eap_sm *sm,
				  struct eap_fast_data *data, u8 flags,
				  const u8 *pos, size_t left)
{
	const u8 *a_id;
	size_t a_id_len;

	/* EAP-FAST Version negotiation (section 3.1) */
	wpa_printf(MSG_DEBUG, "EAP-FAST: Start (server ver=%d, own ver=%d)",
		   flags & EAP_TLS_VERSION_MASK, data->fast_version);
	if ((flags & EAP_TLS_VERSION_MASK) < data->fast_version)
		data->fast_version = flags & EAP_TLS_VERSION_MASK;
	wpa_printf(MSG_DEBUG, "EAP-FAST: Using FAST version %d",
		   data->fast_version);

	a_id = eap_fast_get_a_id(pos, left, &a_id_len);
	eap_fast_select_pac(data, a_id, a_id_len);

	if (data->resuming && data->current_pac) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Trying to resume session - "
			   "do not add PAC-Opaque to TLS ClientHello");
		if (eap_fast_clear_pac_opaque_ext(sm, data) < 0)
			return -1;
	} else if (data->current_pac) {
		/*
		 * PAC found for the A-ID and we are not resuming an old
		 * session, so add PAC-Opaque extension to ClientHello.
		 */
		if (eap_fast_use_pac_opaque(sm, data, data->current_pac) < 0)
			return -1;
	} else {
		/* No PAC found, so we must provision one. */
		if (!data->provisioning_allowed) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: No PAC found and "
				   "provisioning disabled");
			return -1;
		}
		wpa_printf(MSG_DEBUG, "EAP-FAST: No PAC found - "
			   "starting provisioning");
		if (eap_fast_set_provisioning_ciphers(sm, data) < 0 ||
		    eap_fast_clear_pac_opaque_ext(sm, data) < 0)
			return -1;
		data->provisioning = 1;
	}

	return 0;
}