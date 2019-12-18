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
struct eap_fast_data {int session_ticket_used; int provisioning; TYPE_1__* current_pac; scalar_t__ provisioning_allowed; } ;
struct TYPE_2__ {int /*<<< orphan*/  pac_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_fast_derive_master_secret (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_fast_session_ticket_cb(void *ctx, const u8 *ticket, size_t len,
				      const u8 *client_random,
				      const u8 *server_random,
				      u8 *master_secret)
{
	struct eap_fast_data *data = ctx;

	wpa_printf(MSG_DEBUG, "EAP-FAST: SessionTicket callback");

	if (client_random == NULL || server_random == NULL ||
	    master_secret == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: SessionTicket failed - fall "
			   "back to full TLS handshake");
		data->session_ticket_used = 0;
		if (data->provisioning_allowed) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: Try to provision a "
				   "new PAC-Key");
			data->provisioning = 1;
			data->current_pac = NULL;
		}
		return 0;
	}

	wpa_hexdump(MSG_DEBUG, "EAP-FAST: SessionTicket", ticket, len);

	if (data->current_pac == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: No PAC-Key available for "
			   "using SessionTicket");
		data->session_ticket_used = 0;
		return 0;
	}

	eap_fast_derive_master_secret(data->current_pac->pac_key,
				      server_random, client_random,
				      master_secret);

	data->session_ticket_used = 1;

	return 1;
}