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
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_fast_data {int /*<<< orphan*/  simck; scalar_t__ simck_idx; TYPE_1__ ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_FAST_SIMCK_LEN ; 
 int /*<<< orphan*/  EAP_FAST_SKS_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * eap_fast_derive_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_fast_derive_key_auth(struct eap_sm *sm,
				     struct eap_fast_data *data)
{
	u8 *sks;

	/* RFC 4851, Section 5.1:
	 * Extra key material after TLS key_block: session_key_seed[40]
	 */

	sks = eap_fast_derive_key(sm->ssl_ctx, data->ssl.conn,
				  EAP_FAST_SKS_LEN);
	if (sks == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Failed to derive "
			   "session_key_seed");
		return;
	}

	/*
	 * RFC 4851, Section 5.2:
	 * S-IMCK[0] = session_key_seed
	 */
	wpa_hexdump_key(MSG_DEBUG,
			"EAP-FAST: session_key_seed (SKS = S-IMCK[0])",
			sks, EAP_FAST_SKS_LEN);
	data->simck_idx = 0;
	os_memcpy(data->simck, sks, EAP_FAST_SIMCK_LEN);
	os_free(sks);
}