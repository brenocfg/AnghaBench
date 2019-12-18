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
struct milenage_parameters {int /*<<< orphan*/  ki; int /*<<< orphan*/  opc; } ;
struct gsm_triplet {int /*<<< orphan*/ * _rand; int /*<<< orphan*/ * sres; int /*<<< orphan*/ * kc; int /*<<< orphan*/  imsi; } ;

/* Variables and functions */
 int EAP_SIM_MAX_CHAL ; 
 int atoi (char*) ; 
 struct gsm_triplet* get_gsm_triplet (char*) ; 
 struct milenage_parameters* get_milenage (char*) ; 
 int /*<<< orphan*/  gsm_milenage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,int) ; 
 int snprintf (char*,int,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sim_req_auth(char *imsi, char *resp, size_t resp_len)
{
	int count, max_chal, ret;
	char *pos;
	char *rpos, *rend;
	struct milenage_parameters *m;
	struct gsm_triplet *g;

	resp[0] = '\0';

	pos = strchr(imsi, ' ');
	if (pos) {
		*pos++ = '\0';
		max_chal = atoi(pos);
		if (max_chal < 1 || max_chal > EAP_SIM_MAX_CHAL)
			max_chal = EAP_SIM_MAX_CHAL;
	} else
		max_chal = EAP_SIM_MAX_CHAL;

	rend = resp + resp_len;
	rpos = resp;
	ret = snprintf(rpos, rend - rpos, "SIM-RESP-AUTH %s", imsi);
	if (ret < 0 || ret >= rend - rpos)
		return -1;
	rpos += ret;

	m = get_milenage(imsi);
	if (m) {
		u8 _rand[16], sres[4], kc[8];
		for (count = 0; count < max_chal; count++) {
			if (random_get_bytes(_rand, 16) < 0)
				return -1;
			gsm_milenage(m->opc, m->ki, _rand, sres, kc);
			*rpos++ = ' ';
			rpos += wpa_snprintf_hex(rpos, rend - rpos, kc, 8);
			*rpos++ = ':';
			rpos += wpa_snprintf_hex(rpos, rend - rpos, sres, 4);
			*rpos++ = ':';
			rpos += wpa_snprintf_hex(rpos, rend - rpos, _rand, 16);
		}
		*rpos = '\0';
		return 0;
	}

	count = 0;
	while (count < max_chal && (g = get_gsm_triplet(imsi))) {
		if (strcmp(g->imsi, imsi) != 0)
			continue;

		if (rpos < rend)
			*rpos++ = ' ';
		rpos += wpa_snprintf_hex(rpos, rend - rpos, g->kc, 8);
		if (rpos < rend)
			*rpos++ = ':';
		rpos += wpa_snprintf_hex(rpos, rend - rpos, g->sres, 4);
		if (rpos < rend)
			*rpos++ = ':';
		rpos += wpa_snprintf_hex(rpos, rend - rpos, g->_rand, 16);
		count++;
	}

	if (count == 0) {
		printf("No GSM triplets found for %s\n", imsi);
		ret = snprintf(rpos, rend - rpos, " FAILURE");
		if (ret < 0 || ret >= rend - rpos)
			return -1;
		rpos += ret;
	}

	return 0;
}