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
struct eap_sm {int dummy; } ;
struct eap_peer_config {char* external_sim_resp; } ;
struct eap_aka_data {int res_len; int /*<<< orphan*/  res; int /*<<< orphan*/  ck; int /*<<< orphan*/  ik; int /*<<< orphan*/  rand; int /*<<< orphan*/  auts; } ;

/* Variables and functions */
 int EAP_AKA_AUTS_LEN ; 
 int EAP_AKA_CK_LEN ; 
 int EAP_AKA_IK_LEN ; 
 int /*<<< orphan*/  EAP_AKA_RAND_LEN ; 
 int EAP_AKA_RES_MAX_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ hexstr2bin (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int os_strlen (char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_aka_ext_sim_result(struct eap_sm *sm, struct eap_aka_data *data,
				  struct eap_peer_config *conf)
{
	char *resp, *pos;

	wpa_printf(MSG_DEBUG,
		   "EAP-AKA: Use result from external USIM processing");

	resp = conf->external_sim_resp;
	conf->external_sim_resp = NULL;

	if (os_strncmp(resp, "UMTS-AUTS:", 10) == 0) {
		pos = resp + 10;
		if (hexstr2bin(pos, data->auts, EAP_AKA_AUTS_LEN) < 0)
			goto invalid;
		wpa_hexdump_key(MSG_DEBUG, "EAP-AKA: AUTS", data->auts,
				EAP_AKA_AUTS_LEN);
		os_free(resp);
		return -2;
	}

	if (os_strncmp(resp, "UMTS-AUTH:", 10) != 0) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: Unrecognized external USIM processing response");
		os_free(resp);
		return -1;
	}

	pos = resp + 10;
	wpa_hexdump(MSG_DEBUG, "EAP-AKA: RAND", data->rand, EAP_AKA_RAND_LEN);

	if (hexstr2bin(pos, data->ik, EAP_AKA_IK_LEN) < 0)
		goto invalid;
	wpa_hexdump_key(MSG_DEBUG, "EAP-AKA: IK", data->ik, EAP_AKA_IK_LEN);
	pos += EAP_AKA_IK_LEN * 2;
	if (*pos != ':')
		goto invalid;
	pos++;

	if (hexstr2bin(pos, data->ck, EAP_AKA_CK_LEN) < 0)
		goto invalid;
	wpa_hexdump_key(MSG_DEBUG, "EAP-AKA: CK", data->ck, EAP_AKA_CK_LEN);
	pos += EAP_AKA_CK_LEN * 2;
	if (*pos != ':')
		goto invalid;
	pos++;

	data->res_len = os_strlen(pos) / 2;
	if (data->res_len > EAP_AKA_RES_MAX_LEN) {
		data->res_len = 0;
		goto invalid;
	}
	if (hexstr2bin(pos, data->res, data->res_len) < 0)
		goto invalid;
	wpa_hexdump_key(MSG_DEBUG, "EAP-AKA: RES", data->res, data->res_len);

	os_free(resp);
	return 0;

invalid:
	wpa_printf(MSG_DEBUG, "EAP-AKA: Invalid external USIM processing UMTS-AUTH response");
	os_free(resp);
	return -1;
}