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
struct eap_sm {int /*<<< orphan*/  scard_ctx; scalar_t__ external_sim; } ;
struct eap_sim_data {int** rand; int num_chal; int /*<<< orphan*/ * sres; int /*<<< orphan*/ * kc; } ;
struct eap_peer_config {int password_len; scalar_t__ password; scalar_t__ pcsc; scalar_t__ external_sim_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SIM_KC_LEN ; 
 int /*<<< orphan*/  EAP_SIM_SRES_LEN ; 
 int /*<<< orphan*/  GSM_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct eap_peer_config* eap_get_config (struct eap_sm*) ; 
 int eap_sim_ext_sim_req (struct eap_sm*,struct eap_sim_data*) ; 
 int eap_sim_ext_sim_result (struct eap_sm*,struct eap_sim_data*,struct eap_peer_config*) ; 
 scalar_t__ gsm_milenage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hexstr2bin (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ scard_gsm_auth (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_sim_gsm_auth(struct eap_sm *sm, struct eap_sim_data *data)
{
	struct eap_peer_config *conf;

	wpa_printf(MSG_DEBUG, "EAP-SIM: GSM authentication algorithm");

	conf = eap_get_config(sm);
	if (conf == NULL)
		return -1;

	if (sm->external_sim) {
		if (conf->external_sim_resp)
			return eap_sim_ext_sim_result(sm, data, conf);
		else
			return eap_sim_ext_sim_req(sm, data);
	}

#ifdef PCSC_FUNCS
	if (conf->pcsc) {
		if (scard_gsm_auth(sm->scard_ctx, data->rand[0],
				   data->sres[0], data->kc[0]) ||
		    scard_gsm_auth(sm->scard_ctx, data->rand[1],
				   data->sres[1], data->kc[1]) ||
		    (data->num_chal > 2 &&
		     scard_gsm_auth(sm->scard_ctx, data->rand[2],
				    data->sres[2], data->kc[2]))) {
			wpa_printf(MSG_DEBUG, "EAP-SIM: GSM SIM "
				   "authentication could not be completed");
			return -1;
		}
		return 0;
	}
#endif /* PCSC_FUNCS */

#ifdef CONFIG_SIM_SIMULATOR
	if (conf->password) {
		u8 opc[16], k[16];
		const char *pos;
		size_t i;
		wpa_printf(MSG_DEBUG, "EAP-SIM: Use internal GSM-Milenage "
			   "implementation for authentication");
		if (conf->password_len < 65) {
			wpa_printf(MSG_DEBUG, "EAP-SIM: invalid GSM-Milenage "
				   "password");
			return -1;
		}
		pos = (const char *) conf->password;
		if (hexstr2bin(pos, k, 16))
			return -1;
		pos += 32;
		if (*pos != ':')
			return -1;
		pos++;

		if (hexstr2bin(pos, opc, 16))
			return -1;

		for (i = 0; i < data->num_chal; i++) {
			if (gsm_milenage(opc, k, data->rand[i],
					 data->sres[i], data->kc[i])) {
				wpa_printf(MSG_DEBUG, "EAP-SIM: "
					   "GSM-Milenage authentication "
					   "could not be completed");
				return -1;
			}
			wpa_hexdump(MSG_DEBUG, "EAP-SIM: RAND",
				    data->rand[i], GSM_RAND_LEN);
			wpa_hexdump_key(MSG_DEBUG, "EAP-SIM: SRES",
					data->sres[i], EAP_SIM_SRES_LEN);
			wpa_hexdump_key(MSG_DEBUG, "EAP-SIM: Kc",
					data->kc[i], EAP_SIM_KC_LEN);
		}
		return 0;
	}
#endif /* CONFIG_SIM_SIMULATOR */

#ifdef CONFIG_SIM_HARDCODED
	/* These hardcoded Kc and SRES values are used for testing. RAND to
	 * KC/SREC mapping is very bogus as far as real authentication is
	 * concerned, but it is quite useful for cases where the AS is rotating
	 * the order of pre-configured values. */
	{
		size_t i;

		wpa_printf(MSG_DEBUG, "EAP-SIM: Use hardcoded Kc and SRES "
			   "values for testing");

		for (i = 0; i < data->num_chal; i++) {
			if (data->rand[i][0] == 0xaa) {
				os_memcpy(data->kc[i],
					  "\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7",
					  EAP_SIM_KC_LEN);
				os_memcpy(data->sres[i], "\xd1\xd2\xd3\xd4",
					  EAP_SIM_SRES_LEN);
			} else if (data->rand[i][0] == 0xbb) {
				os_memcpy(data->kc[i],
					  "\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7",
					  EAP_SIM_KC_LEN);
				os_memcpy(data->sres[i], "\xe1\xe2\xe3\xe4",
					  EAP_SIM_SRES_LEN);
			} else {
				os_memcpy(data->kc[i],
					  "\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7",
					  EAP_SIM_KC_LEN);
				os_memcpy(data->sres[i], "\xf1\xf2\xf3\xf4",
					  EAP_SIM_SRES_LEN);
			}
		}
	}

	return 0;

#else /* CONFIG_SIM_HARDCODED */

	wpa_printf(MSG_DEBUG, "EAP-SIM: No GSM authentication algorithm "
		   "enabled");
	return -1;

#endif /* CONFIG_SIM_HARDCODED */
}