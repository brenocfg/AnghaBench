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
struct json_token {scalar_t__ type; int /*<<< orphan*/  string; } ;
struct dpp_authentication {int psk_set; int /*<<< orphan*/ * passphrase; int /*<<< orphan*/  akm; int /*<<< orphan*/  psk; } ;

/* Variables and functions */
 scalar_t__ JSON_STRING ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int PMK_LEN ; 
 int /*<<< orphan*/  dpp_akm_psk (int /*<<< orphan*/ ) ; 
 scalar_t__ dpp_akm_sae (int /*<<< orphan*/ ) ; 
 scalar_t__ hexstr2bin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct json_token* json_get_member (struct json_token*,char*) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int os_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dpp_parse_cred_legacy(struct dpp_authentication *auth,
				 struct json_token *cred)
{
	struct json_token *pass, *psk_hex;

	wpa_printf(MSG_DEBUG, "DPP: Legacy akm=psk credential");

	pass = json_get_member(cred, "pass");
	psk_hex = json_get_member(cred, "psk_hex");

	if (pass && pass->type == JSON_STRING) {
		size_t len = os_strlen(pass->string);

		wpa_hexdump_ascii_key(MSG_DEBUG, "DPP: Legacy passphrase",
				      pass->string, len);
		if (len < 8 || len > 63)
			return -1;
		os_strlcpy(auth->passphrase, pass->string,
			   sizeof(auth->passphrase));
	} else if (psk_hex && psk_hex->type == JSON_STRING) {
		if (dpp_akm_sae(auth->akm) && !dpp_akm_psk(auth->akm)) {
			wpa_printf(MSG_DEBUG,
				   "DPP: Unexpected psk_hex with akm=sae");
			return -1;
		}
		if (os_strlen(psk_hex->string) != PMK_LEN * 2 ||
		    hexstr2bin(psk_hex->string, auth->psk, PMK_LEN) < 0) {
			wpa_printf(MSG_DEBUG, "DPP: Invalid psk_hex encoding");
			return -1;
		}
		wpa_hexdump_key(MSG_DEBUG, "DPP: Legacy PSK",
				auth->psk, PMK_LEN);
		auth->psk_set = 1;
	} else {
		wpa_printf(MSG_DEBUG, "DPP: No pass or psk_hex strings found");
		return -1;
	}

	if (dpp_akm_sae(auth->akm) && !auth->passphrase[0]) {
		wpa_printf(MSG_DEBUG, "DPP: No pass for sae found");
		return -1;
	}

	return 0;
}