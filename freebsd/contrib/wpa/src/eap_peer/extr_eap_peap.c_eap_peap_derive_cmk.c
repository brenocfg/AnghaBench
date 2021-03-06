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
struct eap_peap_data {int /*<<< orphan*/ * cmk; int /*<<< orphan*/ * ipmk; int /*<<< orphan*/  peap_version; int /*<<< orphan*/  phase2_eap_started; scalar_t__ reauth; int /*<<< orphan*/  phase2_success; TYPE_1__ ssl; int /*<<< orphan*/ * key_data; } ;
typedef  int /*<<< orphan*/  isk ;
typedef  int /*<<< orphan*/  imck ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_peap_get_isk (struct eap_sm*,struct eap_peap_data*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int peap_prfplus (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int tls_connection_resumed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_peap_derive_cmk(struct eap_sm *sm, struct eap_peap_data *data)
{
	u8 *tk;
	u8 isk[32], imck[60];
	int resumed, res;

	/*
	 * Tunnel key (TK) is the first 60 octets of the key generated by
	 * phase 1 of PEAP (based on TLS).
	 */
	tk = data->key_data;
	if (tk == NULL)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: TK", tk, 60);

	resumed = tls_connection_resumed(sm->ssl_ctx, data->ssl.conn);
	wpa_printf(MSG_DEBUG,
		   "EAP-PEAP: CMK derivation - reauth=%d resumed=%d phase2_eap_started=%d phase2_success=%d",
		   data->reauth, resumed, data->phase2_eap_started,
		   data->phase2_success);
	if (data->reauth && !data->phase2_eap_started && resumed) {
		/* Fast-connect: IPMK|CMK = TK */
		os_memcpy(data->ipmk, tk, 40);
		wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: IPMK from TK",
				data->ipmk, 40);
		os_memcpy(data->cmk, tk + 40, 20);
		wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: CMK from TK",
				data->cmk, 20);
		return 0;
	}

	if (eap_peap_get_isk(sm, data, isk, sizeof(isk)) < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: ISK", isk, sizeof(isk));

	/*
	 * IPMK Seed = "Inner Methods Compound Keys" | ISK
	 * TempKey = First 40 octets of TK
	 * IPMK|CMK = PRF+(TempKey, IPMK Seed, 60)
	 * (note: draft-josefsson-pppext-eap-tls-eap-10.txt includes a space
	 * in the end of the label just before ISK; is that just a typo?)
	 */
	wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: TempKey", tk, 40);
	res = peap_prfplus(data->peap_version, tk, 40,
			   "Inner Methods Compound Keys",
			   isk, sizeof(isk), imck, sizeof(imck));
	forced_memzero(isk, sizeof(isk));
	if (res < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: IMCK (IPMKj)",
			imck, sizeof(imck));

	os_memcpy(data->ipmk, imck, 40);
	wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: IPMK (S-IPMKj)", data->ipmk, 40);
	os_memcpy(data->cmk, imck + 40, 20);
	wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: CMK (CMKj)", data->cmk, 20);
	forced_memzero(imck, sizeof(imck));

	return 0;
}