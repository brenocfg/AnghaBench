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
struct milenage_parameters {int* sqn; int res_len; int /*<<< orphan*/  ki; int /*<<< orphan*/  amf; int /*<<< orphan*/  opc; } ;

/* Variables and functions */
 int EAP_AKA_AUTN_LEN ; 
 int EAP_AKA_CK_LEN ; 
 int EAP_AKA_IK_LEN ; 
 int EAP_AKA_RAND_LEN ; 
 int EAP_AKA_RES_MAX_LEN ; 
 int EAP_AKA_RES_MIN_LEN ; 
 int /*<<< orphan*/  db_update_milenage_sqn (struct milenage_parameters*) ; 
 struct milenage_parameters* get_milenage (char*) ; 
 int /*<<< orphan*/  inc_sqn (int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  milenage_generate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,int) ; 
 int snprintf (char*,int,char*,...) ; 
 int sqn_changes ; 
 scalar_t__ stdout_debug ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int aka_req_auth(char *imsi, char *resp, size_t resp_len)
{
	/* AKA-RESP-AUTH <IMSI> <RAND> <AUTN> <IK> <CK> <RES> */
	char *pos, *end;
	u8 _rand[EAP_AKA_RAND_LEN];
	u8 autn[EAP_AKA_AUTN_LEN];
	u8 ik[EAP_AKA_IK_LEN];
	u8 ck[EAP_AKA_CK_LEN];
	u8 res[EAP_AKA_RES_MAX_LEN];
	size_t res_len;
	int ret;
	struct milenage_parameters *m;
	int failed = 0;

	m = get_milenage(imsi);
	if (m) {
		if (random_get_bytes(_rand, EAP_AKA_RAND_LEN) < 0)
			return -1;
		res_len = EAP_AKA_RES_MAX_LEN;
		inc_sqn(m->sqn);
#ifdef CONFIG_SQLITE
		db_update_milenage_sqn(m);
#endif /* CONFIG_SQLITE */
		sqn_changes = 1;
		if (stdout_debug) {
			printf("AKA: Milenage with SQN=%02x%02x%02x%02x%02x%02x\n",
			       m->sqn[0], m->sqn[1], m->sqn[2],
			       m->sqn[3], m->sqn[4], m->sqn[5]);
		}
		milenage_generate(m->opc, m->amf, m->ki, m->sqn, _rand,
				  autn, ik, ck, res, &res_len);
		if (m->res_len >= EAP_AKA_RES_MIN_LEN &&
		    m->res_len <= EAP_AKA_RES_MAX_LEN &&
		    m->res_len < res_len)
			res_len = m->res_len;
	} else {
		printf("Unknown IMSI: %s\n", imsi);
#ifdef AKA_USE_FIXED_TEST_VALUES
		printf("Using fixed test values for AKA\n");
		memset(_rand, '0', EAP_AKA_RAND_LEN);
		memset(autn, '1', EAP_AKA_AUTN_LEN);
		memset(ik, '3', EAP_AKA_IK_LEN);
		memset(ck, '4', EAP_AKA_CK_LEN);
		memset(res, '2', EAP_AKA_RES_MAX_LEN);
		res_len = EAP_AKA_RES_MAX_LEN;
#else /* AKA_USE_FIXED_TEST_VALUES */
		failed = 1;
#endif /* AKA_USE_FIXED_TEST_VALUES */
	}

	pos = resp;
	end = resp + resp_len;
	ret = snprintf(pos, end - pos, "AKA-RESP-AUTH %s ", imsi);
	if (ret < 0 || ret >= end - pos)
		return -1;
	pos += ret;
	if (failed) {
		ret = snprintf(pos, end - pos, "FAILURE");
		if (ret < 0 || ret >= end - pos)
			return -1;
		pos += ret;
		return 0;
	}
	pos += wpa_snprintf_hex(pos, end - pos, _rand, EAP_AKA_RAND_LEN);
	*pos++ = ' ';
	pos += wpa_snprintf_hex(pos, end - pos, autn, EAP_AKA_AUTN_LEN);
	*pos++ = ' ';
	pos += wpa_snprintf_hex(pos, end - pos, ik, EAP_AKA_IK_LEN);
	*pos++ = ' ';
	pos += wpa_snprintf_hex(pos, end - pos, ck, EAP_AKA_CK_LEN);
	*pos++ = ' ';
	pos += wpa_snprintf_hex(pos, end - pos, res, res_len);

	return 0;
}